#include "headers.h"

void executeChildProcess(char **commandArray)
{
    int check = execvp(commandArray[0], commandArray);
    if (check == -1)
    {
        printf("%s is invalid command!\n", commandArray[0]);
    }
    return;
}
void execVP(char* com,int bg)
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
    strcpy(t, com);
    token = __strtok_r(t, del, &ptr_out);
    i = 0;
    while (token != NULL)
    {
        strcpy(array[i++], token);
        token = __strtok_r(NULL, del, &ptr_out);
    }
    array[i] = NULL;
    int child = fork();
    int status;
    if (child == 0)
    {
        executeChildProcess(array);
        exit(0);
    }
    else if (child < 0)
    {
        printf("fork failed!\n");
        error1();
    }
    else
    {
        if (bg==1)
        {
            printf("[%d]\n", child);
            insertcommandinrecord(child, array[0]);
        }
        else
            waitpid(child, &status, 0);
        // printf("hello\n");
    }
    destroystringlist(array, 100);
    return;
}