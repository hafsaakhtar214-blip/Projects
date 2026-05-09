from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from typing import List
import pandas as pd
import json
import os
from datetime import datetime

# ---------------- FILE SETUP ----------------
USERS_FILE = "data/users.json"
TRANSACTIONS_FILE = "data/transactions.json"
os.makedirs("data", exist_ok=True)

# Initialize files if not exist
for f in [USERS_FILE, TRANSACTIONS_FILE]:
    if not os.path.exists(f) or os.path.getsize(f) == 0:
        with open(f, "w") as file:
            json.dump([], file)


transactions_df = pd.read_csv("data/groceryshop_preprocessed.csv")
customer_clusters_df = pd.read_csv("data/customer_clusters_KMeans.csv")
transactions_df["CustomerID_enc"] = transactions_df["CustomerID_enc"].astype(int)
customer_clusters_df["CustomerID_enc"] = customer_clusters_df["CustomerID_enc"].astype(int)

data = transactions_df.merge(customer_clusters_df, on="CustomerID_enc")
cluster_product_sales = data.groupby(["Cluster", "Product"])["Quantity"].sum().reset_index()
cluster_products_dict = {}
for cluster in cluster_product_sales["Cluster"].unique():
    products = cluster_product_sales[cluster_product_sales["Cluster"] == cluster]
    cluster_products_dict[cluster] = products.sort_values("Quantity", ascending=False)["Product"].tolist()

class LoyaltyAgent:
    def __init__(self, transactions_file):
        self.transactions_file = transactions_file

    def get_discount(self, customer_id: int) -> float:
        try:
            with open(self.transactions_file, "r") as f:
                transactions = json.load(f)
        except:
            transactions = []
        visits = sum(1 for t in transactions if t["user_id"] == customer_id)
        if visits >= 10:  
            return 0.05 
        return 0.0

class RecommendationAgent:
    def __init__(self, transactions_df, customer_clusters_df, cluster_products_dict):
        self.transactions = transactions_df
        self.customer_clusters = customer_clusters_df
        self.cluster_products_dict = cluster_products_dict

    def recommend(self, customer_id: int, cart: List[str] = [], top_n: int = 5):
        bought_products = set(self.transactions[self.transactions["CustomerID_enc"] == customer_id]["Product"])
        recommendations = []

        favorites = list(bought_products - set(cart))
        recommendations.extend(favorites[:top_n])

        cluster_row = self.customer_clusters[self.customer_clusters["CustomerID_enc"] == customer_id]
        if not cluster_row.empty:
            cluster = cluster_row["Cluster"].values[0]
            cluster_products = self.cluster_products_dict.get(cluster, [])
            for p in cluster_products:
                if p not in recommendations and p not in cart:
                    recommendations.append(p)
                if len(recommendations) >= top_n:
                    break

        if len(recommendations) < top_n:
            popular_products = self.transactions.groupby("Product")["Quantity"].sum().sort_values(ascending=False).index.tolist()
            for p in popular_products:
                if p not in recommendations and p not in cart:
                    recommendations.append(p)
                if len(recommendations) >= top_n:
                    break

        return recommendations[:top_n]

loyalty_agent = LoyaltyAgent(TRANSACTIONS_FILE)
recommend_agent = RecommendationAgent(transactions_df, customer_clusters_df, cluster_products_dict)

app = FastAPI(title="AI Recommendation API")
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)

class CartItem(BaseModel):
    ProductName: str
    quantity: int

class CartRequest(BaseModel):
    customer_id: int
    cart: List[CartItem] = []

class UserModel(BaseModel):
    name: str
    email: str
    password: str

class LoginModel(BaseModel):
    email: str
    password: str

class CheckoutModel(BaseModel):
    user_id: int
    items: List[CartItem]
    total: float
    shipping: dict = {}

# ---------------- ROUTES ----------------
@app.get("/")
def root():
    return {"status": "running"}

@app.post("/api/signup")
def signup(user: UserModel):
    with open(USERS_FILE, "r") as f:
        users = json.load(f)

    if any(u["email"] == user.email for u in users):
        raise HTTPException(status_code=400, detail="User already exists")

    user_dict = user.dict()
    user_dict["id"] = max([u.get("id", 0) for u in users], default=0) + 1
    users.append(user_dict)

    with open(USERS_FILE, "w") as f:
        json.dump(users, f, indent=2)

    return {"status": "success", "user": user_dict}

@app.post("/api/login")
def login(credentials: LoginModel):
    with open(USERS_FILE, "r") as f:
        users = json.load(f)

    user = next((u for u in users if u["email"] == credentials.email and u["password"] == credentials.password), None)
    if not user:
        raise HTTPException(status_code=401, detail="Invalid email or password")

    return {"status": "success", "user": user}

@app.post("/api/checkout")
def checkout(order: CheckoutModel):
    try:
        with open(TRANSACTIONS_FILE, "r") as f:
            transactions = json.load(f)
    except:
        transactions = []

    new_id = max([t.get("transaction_id", 0) for t in transactions], default=0) + 1
    order_dict = order.dict()
    order_dict["transaction_id"] = new_id
    order_dict["date"] = str(datetime.now().date())
    discount = loyalty_agent.get_discount(order.user_id)
    order_dict["discount"] = discount

    transactions.append(order_dict)

    with open(TRANSACTIONS_FILE, "w") as f:
        json.dump(transactions, f, indent=2)
    new_rows = pd.DataFrame([{
        "CustomerID_enc": order.user_id,
        "Product": "CHECKOUT",
        "Quantity": 1
    }])
    global transactions_df
    transactions_df = pd.concat([transactions_df, new_rows], ignore_index=True)

    return {"status": "success", "transaction_id": new_id, "discount": discount}

@app.post("/api/recommend-with-cart")
def recommend_with_cart(request: CartRequest):
    customer_id = request.customer_id
    cart_products = [item.ProductName for item in request.cart]
    recommendations = recommend_agent.recommend(customer_id=customer_id, cart=cart_products, top_n=10)
    discount = loyalty_agent.get_discount(customer_id)
    return {
        "customer_id": customer_id,
        "recommended_products": recommendations[:5],
        "discount": discount
    }
