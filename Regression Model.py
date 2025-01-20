# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, r2_score

file_path = "https://raw.githubusercontent.com/mumer97/Biometric-Algorithm-for-Heart-Rate-and-Blood-Pressure-Monitoring/refs/heads/main/HR_data.csv"  # Replace with the path to your CSV file
df = pd.read_csv(file_path)

# Features and target variable
X = df[["HR"]]  
y = df["MEAN_RR"]  

# Split data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Create and train the regression model
model = LinearRegression()
model.fit(X_train, y_train)

# Extract model coefficients
bpCoeffHR = model.coef_[0]  # Slope 
bpIntercept = model.intercept_  # Intercept

# Predict on the test set
y_pred = model.predict(X_test)

# Evaluate the model
mae = mean_absolute_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

# Output results
print("Model Coefficients:")
print(f"bpCoeffHR (Slope): {bpCoeffHR}")
print(f"bpIntercept (Intercept): {bpIntercept}")
print("\nModel Performance:")
print(f"Mean Absolute Error (MAE): {mae:.2f} mmHg")
print(f"R-squared (R2): {r2:.2f}")

# Save coefficients for use in Arduino
print("\nArduino-ready Coefficients:")
print(f"const float bpIntercept = {bpIntercept:.2f};")
print(f"const float bpCoeffHR = {bpCoeffHR:.2f};")
