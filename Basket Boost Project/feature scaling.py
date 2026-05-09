import pandas as pd
from sklearn.preprocessing import LabelEncoder
df = pd.read_csv("Data.csv")

rows = []

for _, row in df.iterrows():
    products = str(row['TransactionProduct']).split(',')
    quantities = [float(q) for q in str(row['TransactionQuantity']).split(',')]

    if len(products) != len(quantities):
        continue

    for i, p in enumerate(products):
        rows.append({
            'CustomerID': row['CustomerID'].strip(),
            'Product': p.strip(),
            'Quantity': quantities[i]
        })

df_clean = pd.DataFrame(rows)

le_customer = LabelEncoder()
df_clean['CustomerID_enc'] = le_customer.fit_transform(df_clean['CustomerID'])

le_product = LabelEncoder()
df_clean['Product_enc'] = le_product.fit_transform(df_clean['Product'])

df_final = df_clean[
    ['CustomerID', 'CustomerID_enc', 'Product', 'Product_enc', 'Quantity']
]
df_final.to_csv("groceryshop_preprocessed.csv", index=False)

visit_counts = (
    df_final.groupby('CustomerID')
    .size()
    .reset_index(name='VisitCount')
)

visit_counts['EligibleDiscount'] = visit_counts['VisitCount'] > 10

visit_counts.to_csv("customer_visit_counts.csv", index=False)

print(
    "Preprocessing complete.\n"
    "Saved files:\n"
    "- groceryshop_preprocessed.csv\n"
    "- customer_visit_counts.csv"
)
