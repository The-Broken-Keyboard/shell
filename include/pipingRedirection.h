#ifndef PIPINGREDIRECTION_H
#define PIPINGREDIRECTION_H
#include "headers.h"

char* Piping(char *string,int pipeinpipeflag,int so,int si);
char **redirection(struct redirCommands *bhejRahaHuArray, int pos, char *string);
int invalidPipe(char* string);

#endif