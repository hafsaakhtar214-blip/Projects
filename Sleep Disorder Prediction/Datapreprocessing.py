import pandas as pd
from sklearn.preprocessing import OrdinalEncoder, LabelEncoder, StandardScaler
from sklearn.model_selection import train_test_split

# 📥 Load dataset
df = pd.read_csv("Sleep_health_and_lifestyle_dataset.csv")

# 🗑️ Drop useless column
df = df.drop("Person ID", axis=1)

# ❤️ Split Blood Pressure
df[['Systolic_BP', 'Diastolic_BP']] = df['Blood Pressure'].str.split('/', expand=True)
df['Systolic_BP'] = df['Systolic_BP'].astype(int)
df['Diastolic_BP'] = df['Diastolic_BP'].astype(int)
df = df.drop('Blood Pressure', axis=1)

# 👤 Encoding
df = pd.get_dummies(df, columns=['Gender'], drop_first=True)
df = pd.get_dummies(df, columns=['Occupation'], drop_first=True)

# ⚖️ BMI Encoding
df['BMI Category'] = df['BMI Category'].replace('Normal Weight', 'Normal')
ord_enc = OrdinalEncoder(categories=[['Normal', 'Overweight', 'Obese']])
df['BMI Category'] = ord_enc.fit_transform(df[['BMI Category']])

# 🎯 Target Encoding
le = LabelEncoder()
df['Sleep Disorder'] = le.fit_transform(df['Sleep Disorder'])

# 📊 Split features & target
X = df.drop('Sleep Disorder', axis=1)
y = df['Sleep Disorder']

# ✂️ Train-test split FIRST (correct way)
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# ⚖️ Scaling AFTER split (correct)
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

print("Preprocessing Done Successfully!")
print("X_train shape:", X_train.shape)
print("X_test shape:", X_test.shape)

df.to_csv("preprocessed_sleep_data.csv", index=False)
print("Preprocessed dataset saved successfully!")