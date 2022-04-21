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
        for (int i = 0; i < 3; i++){
        
        //must fopen each time so we can get the updated energy
        energy_file = fopen(path, "r");
        while ((read = getline(&line, &len, energy_file)) != -1){
            //Do nothing.
        }

        //gettimeofday(&start, NULL);
        
        //this loop is the dummy code
        for (int j = 0; j<10000; j++){
            a = 17;
            b = 42;
            c = 69;
            a += b;
            b -= c;
            a += c;
        }

        //gettimeofday(&end, NULL);
        //long seconds = (end.tv_sec - start.tv_sec);
        //long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

        //printf("The elapsed time is %ld seconds and %ld micros\n", seconds, micros);
        //printf("line: %s", line);

        fclose(energy_file);
        }
        data = strtoull(line, NULL, 10);  
    }
    while (data == old);
    return old;  
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

    //iterate through the part we want to measure 1000 times
    for (int o = 0; o < 1000; o++){
        unsigned long long int tic, tac, energy;
        tic = 0;
        tac = 69;
        tic = readrapl();
        int a;
        int b;
        a=7;
        b=12;
        a= a+b;
        b=b+a;
        tac = readrapl();
        energy = tac - tic;

        //save the energy of each iteration
        fprintf(fpt, "%llu,%d\n", energy, o);
    }

    fclose(fpt);
    return 0;
}