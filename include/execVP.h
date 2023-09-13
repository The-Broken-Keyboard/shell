#ifndef EXECVP_H
#define EXECVP_H

#include "headers.h"
void handle_c(int sig);
void handle_z(int sig);
void execVP(char* com,int bg);
void executeChildProcess(char **commandArray);

#endif