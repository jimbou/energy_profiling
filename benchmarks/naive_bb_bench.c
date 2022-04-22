#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/time.h>
#include <unistd.h>

#define ITERATIONS 100

unsigned long long int readrapl(unsigned long long int old){
  
    char *path = "/sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj"; // sublirose to me to sosto path 
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned long long int data;
    struct timeval start, end;
    int a, b, c;

    FILE * energy_file;
    gettimeofday(&start, NULL);
    energy_file = fopen(path, "r");

    if (energy_file == NULL)
      exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, energy_file)) != -1){
      //Do nothing.
    }
    data = strtoull(line, NULL, 10);

    fclose(energy_file);
    int count = 0;
    if (old != -1){
      while(1){
        count++;
        if (old != data)
          break;
        //printf("didnt break: %d\n", count);
        energy_file = fopen(path, "r");
        while ((read = getline(&line, &len, energy_file)) != -1){
          //Do nothing.
        }
        data = strtoull(line, NULL, 10);
        fclose(energy_file);
      }
    }

    return data;  
}

int main() {

  /*
  now lets try to measure a certain's "block" of code energy
  we also measure the idle energy in order to extract the final "real" energy
  */

  unsigned long long int tic, tac, energy, idle_tic, idle_tac, idle_energy;
  int a;
  int b;

  FILE * fpt;
  fpt = fopen("naive_block_measurements.csv", "w+"); //You can insert your desired output directory
  fprintf(fpt, "iteration,energy,idle_energy\n");

  for(int o = 0; o < ITERATIONS; o++){
    idle_tic = readrapl(-1);
    idle_tac = readrapl(idle_tic);
    idle_energy = idle_tac - idle_tic;
    printf("idle_energy: %llu\n", idle_energy);


    tic = readrapl(-1);
    
    //code block we want to measure
    //you can experiment with different code blocks
    a=7;
    b=12;
    a= a+b;
    b=b+a;
    
    tac = readrapl(tic);
    
    energy = tac - tic;
    printf("energy: %llu\n", energy);

    fprintf(fpt, "%d,%llu,%llu\n", o, energy, idle_energy);
  }

  fclose(fpt);

  return 0;
}