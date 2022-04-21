import pandas as pd
from matplotlib import pyplot as plt

#Add your own path to csv
path_to_csv = "../../measurements.csv"

#read energy measurements
df = pd.read_csv(path_to_csv)
#print("Contents in csv file:\n", df)

#plot energy of code through the iterations
plt.figure(figsize=(15,7))
plt.plot(df.iteration, df.energy)
plt.xlabel('Iteration', fontsize = 16)
plt.ylabel('Energy (μJ)', fontsize = 16)
plt.show()