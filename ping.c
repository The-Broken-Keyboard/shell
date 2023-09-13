#include "./include/headers.h"

void png(char *string)
{
    int i = 0;
    char **array = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
        array[i] = (char *)malloc(sizeof(char) * 100);
    char t[100];
    char *token;
    char *ptr_out = NULL;
    char del[] = " \t\f\v\r\n";
    token = NULL;
    ptr_out = NULL;
    strcpy(t, string);
    token = __strtok_r(t, del, &ptr_out);
    i = 0;
    while (token != NULL)
    {
        strcpy(array[i++], token);
        token = __strtok_r(NULL, del, &ptr_out);
    }
    if (i > 3 || i < 3)
    {
        fprintf(stderr, RED"invalid ping command!\n"RESET);
        return;
    }
    pid_t pid;
    int signo;
    for (int j = 0; j < 3; j++)
    {
        if (j == 0)
        {
            if (strcmp("ping", array[j]) != 0)
            {
                fprintf(stderr, RED"invalid ping command!\n"RESET);
                return;
            }
        }
        else if(j==1)
        {
            if(numberchecker(array[j]))
            pid=atoi(array[j]);
            else{
                fprintf(stderr,RED"No valid pid given!\n"RESET);
                return;
            }
        }
        else{
            if(numberchecker(array[j]))
            signo=atoi(array[j]);
            else{
                fprintf(stderr,RED"No valid signal number given!\n"RESET);
                return;
            }
            signo=signo%32;
        }
    }
    if(kill(pid,signo)!=0)
    {
        fprintf(stderr,RED"Wrong pid , signal couldn't be sent\n"RESET);
    }
        return;
}