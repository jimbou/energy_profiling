# 2) Energy profiling using intel rapl
This folder contains llvm passes that try to measure the energy consumed by each BB of a programm .


foo.c is the test c file  
foo_func.c the test file for the rapl_func_pass.cpp
rapl_read_1.c is the rapl read function in c   
it is included in the foo c and should be included in all test files  

rapl_pass.cpp is the final pass:


* it first prints for all the bb their id and then their instructions in llvm IR  
* it then adds this instructions in each basic block  
* a print of its id so that we can count how many times it has been executed  
* a call to rapl_read function at the beginning of the bb which prints 2 energy values  
* a call to rapl_read function at the end of the bb which prints 2  additional energy values  
* the substraction of the 4th energy value from the fourth energy value (or even third if it is different from second) is the energy spent by bb + an overhead of half a cycle idle energy on average.

rapl_func_pass.cpp is the final pass for function energy measurment:

 it first prints for all the bb their id and then their instructions in llvm IR  
* it then adds this instructions in each function 
  * a print of its id so that we can count how many times it has been executed  
  * a call to rapl_read function at the beginning of the function which prints 2 energy values  
  * a call to rapl_read function at the end of the function which prints 2  additional energy values  
  * the substraction of the 4th energy value from the fourth energy value (or even third if it is different from second) is the energy spent by function    + an overhead of half a cycle idle energy on average.
* it then adds this instructions in each bb:
  *  a print of its id so that we can count how many times it has been executed   




More detailed explanation :

The idia is threefold : 

* we must first correspond each basic block to a unique id (task 1)
* we must print the contents of each basic block in the form of llvm IR assembly so that we can later perform analytics using python (task2)
* we must count the times each basic block is executed (task 3)
* we must correspond each bb execution to a rapl energy consumption (task4)  

**Task 1:**
The firt approach was to use the getName methods of the functions and basic nlocks which when used together provide a unique identifier for each bb.  
But most of the times the getName of BB returns an empty string which does not satisfy the uniqueness property as all bbs of a function will be named the same.  
So we use the setName method of the bb class using the function name as input . Taking into account the fact that the compiler wont let the names of 2 bb be set to the    same string it will add a postfix number unique to each bb . So this way the nam of each block will be the name of his function plus a unique number at the end. Exception is the first bb of each function which will be named with just the name of the function but will also be unique.

**Task 2:**
This is pretty simple . We just print the basic block using _ errs() << *BB; _    

**Task 3 :**  
We solve this buy adding a instruction (a call to a print function actually) at the beggining of each basic block which prints the basic block's unique name we created in task1 .  
This way if we count all the prints of each bb's name we will know how many times it executed.

**Task 4: **   
The idea is to insert a call function instruction at the beggining and the end of each BB . This function is the raplread function which makes the energy reads .
So if we have a energy value at the beggining of the bb and an energy value at its end we can substract them and have the energy spent by the bb.  
In practise it is a bit harder than that as the rapl reads must be times with the refresh rate of the rapl. Meaning that rapl refreshes its value approx every 1 ms so that if we read energy at some point in time this energy can be obsolete by up to 1ms . So the idea is to read from rapl and wait untill we raid a new value again . When the rapl has just been updated we know for a fact that this new value is brand new and usable by us .  
At the end of the bb we do something similar with a few changes . We read a value and we check of it is different from the value we read at the beginning . If yes then good Luck we keep this value and it is accurate although it might involve up to 1 ms of idle energy (average of 0.5 ms idle energy ) which must be accounted in post processsing . If the value we read is the same as the value we had read at the start of the bb then we must wait for the rapl energy to be updated , read again and use the last value as the  termination energy . THis termination energy as well contains up to 1 ms of idle energy (not so idle as we were performing repeative rapl reads ).

Future tasks --> We must perform rapl reads to measure idle energy so that half of it on average can be substracted from the clculated energy spent by the BB.

