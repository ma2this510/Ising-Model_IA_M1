import numpy as np
import matplotlib.pyplot as plt
import pickle
import os

# Load the data
with open("spins.pkl", "rb") as f:
    data = pickle.load(f)

data = np.array(data)

M = np.loadtxt("moment.dat")

T = np.linspace(0.0, 4.0, 1000)
T_c = 2/np.log(1+np.sqrt(2))
M_th = [(1-np.sinh(2/t)**(-4))**(1/8) if t < T_c else 0 for t in T]

fig, axs = plt.subplots(2, 1, height_ratios=[4,2], sharex=True, figsize=(10, 9.6), constrained_layout=True)
axs[0].imshow(data.T, cmap='winter', interpolation='none', origin='lower', extent=[0, 4, 0, 2])
axs[0].set_yticks([])
axs[0].set_title(r"$\langle s \rangle$")
axs[1].grid(True)
axs[1].errorbar(M[:, 0], M[:, 1], yerr=M[:, 2], fmt='o', color='k', ecolor='k', capsize=2, elinewidth=1, markeredgewidth=1, markersize=1)
axs[1].plot(T, M_th, color='r', linewidth=1)
axs[1].set_xlabel(r"$T$")
axs[1].set_ylabel(r"$\langle m \rangle$")
plt.tight_layout()
plt.savefig("total_plot.png", dpi=300)
plt.show()