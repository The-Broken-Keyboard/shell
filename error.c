#include "./include/headers.h"

void error1(){
    printf("Error no: %d\n",errno);
    perror("Error statement is:");
    // exit(EXIT_FAILURE);
}