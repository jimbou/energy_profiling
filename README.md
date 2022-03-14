# energy_profiling
Energy profiling of c / c++ code using llvm and intel rapl
we will be implementing three types of llvm passes :
1) a code profiling pass counting number of BB , number and type of instructions in each BB etc
2) a energy measuring pass that adds rapl measurig commands at the beggining and end of each BB
3) an energy measuring pass of the computer in idle state which measures the overhead energy consumed 
by the computer so that it can be removed from the measurments we acquired from the second pass
