import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.pipeline import make_pipeline
from sklearn.ensemble import RandomForestRegressor
from sklearn.linear_model import LogisticRegression
from joblib import dump, load
import sys

# https://packaging.python.org/en/latest/guides/installing-using-pip-and-virtual-environments/

# Read the data
df = pd.read_csv('winratios.csv', sep=',', header=0)
print(df.columns)
print(df.head(5))

# Pivot the dataframe to form a 2D matrix of winratio
df_pivot = df.pivot(index='lshp', columns='sshp', values='winratio')

# Now, extract the matrix data from the pivoted dataframe
winratios = df_pivot.values

# Get the ranges for the x and y axes
sshp_range = [df['sshp'].min(), df['sshp'].max()]
lshp_range = [df['lshp'].min(), df['lshp'].max()]

# Display the heatmap
plt.imshow(winratios, cmap='hot', interpolation='nearest',
           extent=sshp_range+lshp_range, origin='lower', aspect='auto')

# Add color bar
plt.colorbar()

# Set labels
plt.xlabel('Short Sword HP')
plt.ylabel('Long Sword HP')

# Save the figure
plt.savefig('winratios.png')

X = df[['sshp', 'lshp']]
y = df['winratio']

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.01, random_state=42)

# Create a Random Forest model
model = RandomForestRegressor(n_estimators=100, random_state=42)

# Train the model
model.fit(X_train, y_train)

# Now you can use the trained model to predict the winratio for any given pair of sshp and lshp
sshp_new = 10  # replace with your value
lshp_new = 20  # replace with your value
winratio_pred = model.predict([[sshp_new, lshp_new]])
print(df[(df['sshp'] == sshp_new) & (df['lshp'] == lshp_new)]['winratio'])

print(
    f"Predicted winratio for sshp={sshp_new} and lshp={lshp_new} is {winratio_pred[0]}")

# Convert winratio to a binary variable: 1 if winratio > 0.5, else 0
df['winratio'] = (df['winratio'] > 0.25).astype(int)

# Extract the features and target
X = df[['sshp', 'lshp']]
y = df['winratio']

# Split the data into training and test sets
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42)

# Create a Logistic Regression model
model = LogisticRegression(random_state=42)

# Train the model
model.fit(X_train, y_train)
# Print the coefficients and intercept
print("Coefficients:", model.coef_)
print("Intercept:", model.intercept_)

# Now you can use the trained model to predict the class for any given pair of sshp and lshp
sshp_new = 100  # replace with your value
lshp_new = 79  # replace with your value
winratio_pred = model.predict([[sshp_new, lshp_new]])

print(
    f"Predicted class for sshp={sshp_new} and lshp={lshp_new} is {winratio_pred[0]}")
