#include "./include/headers.h"
pid_t child;
int sleepflag;
void handle_c(int sig)
{
    printf("\n");
    if (sleepflag == 0)
    {
        prompt();
        input[0]='\0';
    }
    else
    {
        sleepflag = 0;
    }
    return;
}
void handle_z(int sig)
{
    return;
}
void executeChildProcess(char **commandArray)
{
    setpgid(0, 0);
    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    int check = execvp(commandArray[0], commandArray);
    if (check == -1)
    {
        fprintf(stderr, RED "%s is invalid command!\n" RESET, commandArray[0]);
        exit(1);
    }
    return;
}

void execVP(char *com, int bg)
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
    sleepflag = 1;
    child = fork();
    if (child == 0)
    {
        executeChildProcess(array);
        exit(0);
    }
    else if (child < 0)
    {
        fprintf(stderr, RED "fork failed!\n" RESET);
    }
    else
    {

        if (bg == 1)
        {
            // printf("[%d]\n", child);
            printf("[%d]\n", child);
            insertcommandinrecord(child, array[0]);
        }
        else
        {
            setpgid(child, 0);
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0, child);

            int status;
            waitpid(child, &status, WUNTRACED);

            if (WIFSTOPPED(status))
            {
                insertcommandinrecord(child, array[0]);
            }

            tcsetpgrp(0, getpgid(0));
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
    }
    destroystringlist(array, 100);
    return;
}