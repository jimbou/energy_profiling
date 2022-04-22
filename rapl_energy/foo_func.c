#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void print(char str[])
{
    printf("String Output: ");
    puts(str);
}*/

void printbb(char *s) {
    printf("Basic block : %s\n", s);
}

void printfunc(char *s) {
    printf("Function : %s\n", s);
}



void readrapl() {
  
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
    printf("old: %llu\n", old);

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
    printf("new: %llu\n", data);
    return ; 
}


void hello() {
   printf("hello world\n");
    return;
}

int main() {
    int a;
    scanf("%d", &a);
    if (a>2){
    hello();   
    }
    else{
      printf("hello world_2\n");   
    }
    return 0;
}
