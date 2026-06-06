import pandas as pd
from sklearn.preprocessing import OrdinalEncoder, LabelEncoder, StandardScaler
from sklearn.model_selection import train_test_split

# 1. Load dataset
df = pd.read_csv("sleep_data.csv")

# 2. Drop ID column
df.drop("Person ID", axis=1, inplace=True)

# 3. Split Blood Pressure
df[["Systolic", "Diastolic"]] = df["Blood Pressure"].str.split("/", expand=True)
df["Systolic"] = df["Systolic"].astype(int)
df["Diastolic"] = df["Diastolic"].astype(int)
df.drop("Blood Pressure", axis=1, inplace=True)

# 4. Encode Gender
df["Gender"] = df["Gender"].map({"Male": 0, "Female": 1})

# 5. Fix BMI (Ordinal)
df["BMI Category"] = df["BMI Category"].replace("Normal Weight", "Normal")
ord_enc = OrdinalEncoder(categories=[["Normal", "Overweight", "Obese"]])
df["BMI Category"] = ord_enc.fit_transform(df[["BMI Category"]])

# 6. One-hot encode Occupation
df = pd.get_dummies(df, columns=["Occupation"], drop_first=True)

# 7. Encode target
le = LabelEncoder()
df["Sleep Disorder"] = le.fit_transform(df["Sleep Disorder"])

# 8. Handle missing values
df.fillna(df.mean(numeric_only=True), inplace=True)

# ✅ DEFINE FEATURES AND TARGET (YOU MISSED THIS)
X = df.drop("Sleep Disorder", axis=1)
y = df["Sleep Disorder"]

# ✂️ Train-test split
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# ⚖️ Scaling AFTER split
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

print("Preprocessing Done Successfully!")
print("X_train shape:", X_train.shape)
print("X_test shape:", X_test.shape)

# 9. SAVE FINAL PREPROCESSED DATA
df.to_csv("preprocessed_sleep_data_future.csv", index=False)

print("Preprocessed dataset saved successfully!")