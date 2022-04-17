# 2) Energy profiling using intel rapl
This folder contains llvm passes that try to measure the energy consumed by each BB of a programm .


foo.c is the test c file 
rapl_read_1.c is the rapl read function in c it is included in the foo c and should be included in all test files

rapl_pass.cpp is the final pass:

it first prints for all the bb their id and then their instructions in llvm IR

it then adds this instructions in each basic block

a print of its id so that we can count how many times it has been executed

a call to rapl_read function at the beginning of the bb which prints 2 energy values

a call to rapl_read function at the end of the bb which prints 2  additional energy values

the substraction of the 4th energy value from the fourth energy value (or even third if it is different from second) is the energy spent by bb + an overhead of half a cycle idle energy on average.
