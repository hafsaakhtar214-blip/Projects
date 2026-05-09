import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from sklearn.cluster import KMeans
from keras.models import Model
from keras.layers import Input, Dense
from sklearn.metrics import silhouette_score

df = pd.read_csv("./Data/groceryshop_preprocessed.csv")

matrix = df.pivot_table(
    index='CustomerID_enc',
    columns='Product_enc',
    values='Quantity',
    aggfunc='sum',
    fill_value=0
)

scaler = MinMaxScaler()
X = scaler.fit_transform(matrix)

input_dim = X.shape[1]
latent_dim = 10   

input_layer = Input(shape=(input_dim,))
encoded = Dense(64, activation='relu')(input_layer)
encoded = Dense(32, activation='relu')(encoded)
latent = Dense(latent_dim, activation='relu')(encoded)

decoded = Dense(32, activation='relu')(latent)
decoded = Dense(64, activation='relu')(decoded)
output_layer = Dense(input_dim, activation='sigmoid')(decoded)

autoencoder = Model(input_layer, output_layer)
autoencoder.compile(optimizer='adam', loss='mse')

autoencoder.fit(
    X, X,
    epochs=40,
    batch_size=32,
    validation_split=0.1,
    shuffle=True
)

X_reconstructed = autoencoder.predict(X)

rmse = np.sqrt(np.mean((X - X_reconstructed) ** 2))
print("Reconstruction RMSE:", rmse)

encoder = Model(input_layer, latent)
latent_features = encoder.predict(X)

kmeans = KMeans(n_clusters=5, random_state=42)
clusters = kmeans.fit_predict(latent_features)

sil_score = silhouette_score(latent_features, clusters)
print("Silhouette Score:", sil_score)

customer_clusters = pd.DataFrame({
    'CustomerID_enc': matrix.index,
    'Cluster': clusters
})

customer_clusters.to_csv("customer_clusters_KMeans.csv", index=False)

print("Autoencoder + RMSE + Clustering completed successfully.")
