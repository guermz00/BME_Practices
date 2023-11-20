# Make sure to pip install tensorflow

import tensorflow as tf
import numpy as np

# Create a dataset of pairs of numbers and their sum
inputs = np.array([[i, j] for i in range(50) for j in range(50)])
targets = np.array([i + j for i in range(50) for j in range(50)])

# Model configuration
model = tf.keras.Sequential([
    tf.keras.layers.Dense(64, activation='relu', input_shape=(2,)),
    tf.keras.layers.Dense(64, activation='relu'),
    tf.keras.layers.Dense(1)
])

model.compile(optimizer='adam', loss='mean_squared_error')

# Train the model
model.fit(inputs, targets, epochs=10)

# Test the model
test_input = np.array([[10, 15]])
print("Test Input: [10, 15]")
print("Predicted Sum:", model.predict(test_input)[0][0])
