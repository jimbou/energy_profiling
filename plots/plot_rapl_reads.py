import pandas as pd
from matplotlib import pyplot as plt
import sys

#Add your measurements csv file as argument
path_to_csv = sys.argv[1]

#read energy measurements
df = pd.read_csv(path_to_csv)
#print("Contents in csv file:\n", df)


#plot energy of code through the iterations
plt.figure(figsize=(15,7))
plt.plot(df.iteration, df.energy, label = 'energy')
if df.shape[1] > 2:
    plt.plot(df.iteration, df.idle_energy, label = 'idle energy')
plt.xlabel('Iteration', fontsize = 16)
plt.ylabel('Energy (μJ)', fontsize = 16)
plt.legend()
plt.show()