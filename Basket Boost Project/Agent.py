import pandas as pd
import random

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

cluster_products_dict = {}
for cluster in cluster_product_sales['Cluster'].unique():
    products = cluster_product_sales[cluster_product_sales['Cluster'] == cluster]
    products_sorted = products.sort_values('Quantity', ascending=False)['Product_enc'].tolist()
    cluster_products_dict[cluster] = products_sorted

class RecommendationAgent:
    def __init__(self, transactions_df, customer_clusters_df, cluster_products_dict):
        self.transactions = transactions_df
        self.customer_clusters = customer_clusters_df
        self.cluster_products_dict = cluster_products_dict
    
    def recommend(self, customer_id, top_n=5):
        row = self.customer_clusters[
            self.customer_clusters['CustomerID_enc'] == customer_id
        ]
        if row.empty:
            return []  
        
        cluster = row['Cluster'].values[0]
        
        bought_products = set(
            self.transactions[
                self.transactions['CustomerID_enc'] == customer_id
            ]['Product_enc']
        )

        cluster_products = self.cluster_products_dict.get(cluster, [])
        random.shuffle(cluster_products)
        recommendations = [p for p in cluster_products if p not in bought_products]
        if len(recommendations) < top_n:
            for p in cluster_products:
                if p not in recommendations:
                    recommendations.append(p)
                if len(recommendations) >= top_n:
                    break
        
        return recommendations[:top_n]

recommend_agent = RecommendationAgent(transactions, customer_clusters, cluster_products_dict)

sample_customer = int(customer_clusters.sample(1)['CustomerID_enc'].values[0])

print("=== SAMPLE CUSTOMER RESULT ===")
print("Customer ID:", sample_customer)
print("Recommended Products:", recommend_agent.recommend(sample_customer))
