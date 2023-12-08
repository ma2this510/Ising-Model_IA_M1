import numpy as np
import matplotlib.pyplot as plt
import pickle

# Load the data
with open("spins.pkl", "rb") as f:
    data = pickle.load(f)

data = np.array(data)

plt.figure(figsize=(10, 6))
plt.imshow(data.T, cmap='winter', interpolation='none', origin='lower', extent=[0, 4, 0, 2])

plt.title("Ising model")
plt.tight_layout()
# plt.savefig("ising.png")
plt.show()