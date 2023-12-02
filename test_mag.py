import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Read in the data
df = np.loadtxt('mydata/couche_40_2.30.txt')
# Plot the data
plt.imshow(df, cmap='gray')
plt.show()