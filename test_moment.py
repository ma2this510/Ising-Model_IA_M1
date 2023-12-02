import pandas as pd
import matplotlib.pyplot as plt


# Import moment.dat and skip first line
data = pd.read_csv('moment.dat', skiprows=1, sep='\s+')
data.columns = ['T', 'moy', 'std']
print(data.info())

# Plot the data
plt.errorbar(data['T'], data['moy'], yerr=data['std'], fmt='o', ms=3, capsize=1)
plt.xlabel('T')
plt.ylabel('m')
plt.show()


