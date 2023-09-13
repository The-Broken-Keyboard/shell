#include "./include/headers.h"

void fg(char *string)
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
    if (i > 2)
    {
        fprintf(stderr,RED"Invalid command of fg!\n"RESET);
        return;
    }
    if (strcmp(array[0], "fg") != 0)
    {
        fprintf(stderr,RED"invalid command of fg!\n"RESET);
        return;
    }
    if (!numberchecker(array[1]))
    {
        fprintf(stderr, RED"No pid given\n"RESET);
        return;
    }
    pid_t pid = atoi(array[1]);
    if (kill(pid, SIGCONT) != 0)
    {
        fprintf(stderr, RED"No such process found with pid %d!\n"RESET, pid);
        return;
    }
    setpgid(pid, 0);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, pid);

    int status;
    waitpid(pid, &status, WUNTRACED);
    if (WIFSTOPPED(status))
    {
        printf(YELLOW"process with pid[%d] stopped\n"RESET, pid);
    }
    else
    {
        if (recordHead->next != recordHead)
        {
            struct recordOfCommands *temp = recordHead->next;
            struct recordOfCommands *next;
            while (temp != recordHead)
            {
                if (temp->pid == pid)
                    break;
            }
            removenodeFromRecordlist(temp);
        }
        printf(YELLOW"process with pid[%d] exited normally!\n"RESET, pid);
    }

    tcsetpgrp(0, getpgid(0));
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}

void bg(char *string)
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
    if (i > 2)
    {
        fprintf(stderr, RED"Invalid command of bg!\n"RESET);
        return;
    }
    if (strcmp(array[0], "bg") != 0)
    {
        fprintf(stderr, RED"invalid command of bg!\n"RESET);
        return;
    }
    if (!numberchecker(array[1]))
    {
        fprintf(stderr, RED"No pid given\n"RESET);
        return;
    }
    pid_t pid = atoi(array[1]);
    if (kill(pid, SIGCONT) != 0)
    {
        fprintf(stderr, RED"NO such process found with pid %d\n"RESET, pid);
    }
    return;
}