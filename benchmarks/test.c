#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/time.h>
#include <unistd.h>

int readrapl() {
  
    /*
    readrapl function returns the rapl energy at a specific time
    we have included some "dummy" code because to increase the energy consumption of this 1st experiment
    */

    char *path = "/sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj"; // sublirose to me to sosto path 
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned long long int old ,data;
    struct timeval start, end;
    int a, b, c;

    FILE * energy_file = fopen(path, "r");

    if (energy_file == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, energy_file)) != -1){
        //Do nothing.
    }

    old = strtoull(line, NULL, 10);
    fclose(energy_file);

    do {        
        //must fopen each time so we can get the updated energy
        energy_file = fopen(path, "r");
        while ((read = getline(&line, &len, energy_file)) != -1){
            //Do nothing.
        }

        fclose(energy_file);
        
        data = strtoull(line, NULL, 10);  
    }
    while (data == old);
    return data;  
}

int main() {

    /*
    As a first experiment we will measure the energy of a program's main body
    In order to understand the energy variation of different runs, we execute the program 1000 times
    */

    //make the output csv
    FILE * fpt;
    fpt = fopen("measurements.csv", "w+"); //You can insert your desired output directory
    fprintf(fpt, "energy,iteration\n");
    int a;
    int b;
    //iterate through the part we want to measure 1000 times
    unsigned long long int energy_10000=0;
    fprintf(fpt, "size=10000\n");
    for (int o = 0; o < 1000; o++){
        unsigned long long int tic, tac, energy;
        tic = 0;
        tac = 69;
        tic = readrapl();
        
        for (int i =0; i< 10000 ; i++){
        a=7;
        b=12;
        a= a+b;
        b=b+a;
        a=b-9;
        b=b*a;
        }
        tac = readrapl();
        energy = tac - tic;
        energy_10000 += energy;
        //save the energy of each iteration
        fprintf(fpt, "%llu,%d\n", energy, o);
    }

    unsigned long long int energy_100000=0;
    fprintf(fpt, "\nsize=100000\n");
    for (int o = 0; o < 100; o++){
        unsigned long long int tic, tac, energy;
        tic = 0;
        tac = 69;
        tic = readrapl();
        
        for (int i =0; i< 100000 ; i++){
        a=7;
        b=12;
        a= a+b;
        b=b+a;
        a=b-9;
        b=b*a;
        }
        tac = readrapl();
        energy = tac - tic;
        energy_100000 += energy;
        //save the energy of each iteration
        fprintf(fpt, "%llu,%d\n", energy, o);
    }

    unsigned long long int energy_1000000=0;
    fprintf(fpt, "\nsize=1000000\n");
    for (int o = 0; o < 10; o++){
        unsigned long long int tic, tac, energy;
        tic = 0;
        tac = 69;
        tic = readrapl();
        
        for (int i =0; i< 1000000 ; i++){
        a=7;
        b=12;
        a= a+b;
        b=b+a;
        a=b-9;
        b=b*a;
        }
        tac = readrapl();
        energy = tac - tic;
        energy_1000000 += energy;

        //save the energy of each iteration
        fprintf(fpt, "%llu,%d\n", energy, o);
    }

    fprintf(fpt, "\nsize=1000000\n");
    unsigned long long int energy_10000000=0;
    for (int o = 0; o < 1; o++){
        unsigned long long int tic, tac, energy;
        tic = 0;
        tac = 69;
        tic = readrapl();
        
        for (int i =0; i< 10000000 ; i++){
        a=7;
        b=12;
        a= a+b;
        b=b+a;
        a=b-9;
        b=b*a;
        }
        tac = readrapl();
        energy = tac - tic;
        energy_10000000 += energy;
        //save the energy of each iteration
        fprintf(fpt, "%llu,%d\n", energy, o);
    }

     fprintf(fpt, "Energy of 10000: %llu\n", energy_10000);
     fprintf(fpt, "Energy of 100000: %llu\n", energy_100000);
     fprintf(fpt, "Energy of 1000000: %llu\n", energy_1000000);
     fprintf(fpt, "Energy of 10000000: %llu\n", energy_10000000);


    

    fclose(fpt);
    return 0;
}