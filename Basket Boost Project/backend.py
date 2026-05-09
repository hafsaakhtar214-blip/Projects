import pandas as pd

transactions = pd.read_csv("./Data/groceryshop_preprocessed.csv")
customer_clusters = pd.read_csv("./Data/customer_clusters_KMeans.csv")

transactions['CustomerID_enc'] = transactions['CustomerID_enc'].astype(int)
customer_clusters['CustomerID_enc'] = customer_clusters['CustomerID_enc'].astype(int)

data = transactions.merge(customer_clusters, on="CustomerID_enc")

cluster_product_sales = (
    data.groupby(['Cluster', 'Product_enc'])['Quantity']
    .sum()
    .reset_index()
)

TOP_N = 5

cluster_recommendations = (
    cluster_product_sales
    .sort_values(['Cluster', 'Quantity'], ascending=[True, False])
    .groupby('Cluster')
    .head(TOP_N)
)

cluster_recommendations.to_csv(
    "cluster_product_recommendations.csv",
    index=False
)

print("\n=== PRODUCT RECOMMENDATIONS PER CLUSTER ===")
print(cluster_recommendations.head(10))

customer_visits = (
    transactions.groupby('CustomerID_enc')
    .size()
    .reset_index(name='VisitCount')
)

def loyalty_discount(visits):
    if visits >= 10:
        return 0.05
    else:
        return 0.0

customer_loyalty = customer_visits.merge(
    customer_clusters, on="CustomerID_enc"
)

customer_loyalty['Discount'] = customer_loyalty['VisitCount'].apply(
    loyalty_discount
)

customer_loyalty.to_csv(
    "customer_loyalty_discounts.csv",
    index=False
)

print("\n=== CUSTOMER LOYALTY DISCOUNTS ===")
print(customer_loyalty.head(10))

def recommend_products(customer_id, top_n=5):
    row = customer_clusters[
        customer_clusters['CustomerID_enc'] == customer_id
    ]

    if row.empty:
        return []

    cluster = row['Cluster'].values[0]

    bought_products = set(
        transactions[
            transactions['CustomerID_enc'] == customer_id
        ]['Product_enc']
    )

    cluster_products = cluster_recommendations[
        cluster_recommendations['Cluster'] == cluster
    ]['Product_enc'].tolist()

    recommendations = [
        p for p in cluster_products if p not in bought_products
    ]

    return recommendations[:top_n]

sample_customer = int(customer_loyalty.iloc[0]['CustomerID_enc'])

print("\n=== SAMPLE CUSTOMER RESULT ===")
print("Customer ID:", sample_customer)
print("Recommended Products:", recommend_products(sample_customer))
print(
    "Discount:",
    f"{int(customer_loyalty.iloc[0]['Discount'] * 100)}%"
)

print("\n Backend processing completed successfully.")
