# energy_profiling
Energy profiling of c / c++ code using llvm and intel rapl
we will be implementing three types of llvm passes :
1) a code profiling pass counting number of BB , number and type of instructions in each BB etc
2) a energy measuring pass that adds rapl measurig commands at the beggining and end of each BB
3) an energy measuring pass of the computer in idle state which measures the overhead energy consumed 
by the computer so that it can be removed from the measurments we acquired from the second pass


We have included 2 more folders :
1) for the preprocessing of the data produced by the llvm passes
2) for the creation of an energy prediction mechnanism based on the preprocessed data

How to run an llvm pass:

# rapl read
To read rapl measurements you first need to enter the following line into the terminal:
```
sudo chmod -R a+r /sys/class/powercap/intel-rapl
```
