import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, r2_score

# Example Dataset: Replace this with actual data
# Columns: PTT (seconds), BP_Systolic (mmHg)
data = {
    "PTT": [0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60],
    "BP_Systolic": [120, 118, 115, 110, 105, 100, 95, 90]
}

# Load the data into a pandas DataFrame
df = pd.DataFrame(data)

# Features and target variable
X = df[["PTT"]]  # PTT (independent variable)
y = df["BP_Systolic"]  # BP (dependent variable)

# Split data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Create and train the regression model
model = LinearRegression()
model.fit(X_train, y_train)

# Extract model coefficients
bpCoeffPTT = model.coef_[0]  # Slope (PTT coefficient)
bpIntercept = model.intercept_  # Intercept

# Predict on the test set
y_pred = model.predict(X_test)

# Evaluate the model
mae = mean_absolute_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

# Output results
print("Model Coefficients:")
print(f"bpCoeffPTT (Slope): {bpCoeffPTT}")
print(f"bpIntercept (Intercept): {bpIntercept}")
print("\nModel Performance:")
print(f"Mean Absolute Error (MAE): {mae:.2f} mmHg")
print(f"R-squared (R2): {r2:.2f}")

# Save coefficients for use in Arduino
print("\nArduino-ready Coefficients:")
print(f"const float bpIntercept = {bpIntercept:.2f};")
print(f"const float bpCoeffPTT = {bpCoeffPTT:.2f};")
