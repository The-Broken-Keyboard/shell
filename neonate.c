#include "./include/headers.h"
int alrmtime;
int alarmflag;
int kbhit()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}
int numberchecker(char *string)
{
    int size = strlen(string);
    for (int i = 0; i < size; i++)
    {
        if (string[i] <= 57 && string[i] >= 48)
        {
            continue;
        }
        else
            return 0;
    }
    return 1;
}
void neonatefunc(int sig)
{

    if (!alarmflag)
    {
        char path[500];
        sprintf(path, "/proc/loadavg");
        FILE *fptr = fopen(path, "r");
        if (fptr == NULL)
        {
            fprintf(stderr, RED "file didn't open \n" RESET);
            error1();
        }
        char string[5000];
        fread(string, sizeof(char), 5000, fptr);
        char garb[100];
        pid_t pidno;
        sscanf(string, "%s %s %s %s %d", garb, garb, garb, garb, &pidno);
        printf(WHITE"%d\n"RESET, pidno);
        alarm(alrmtime);
        return;
    }
}
void neonate(char *string)
{
    alarmflag=0;
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
    if (strcmp(array[0], "neonate") != 0)
    {
        fprintf(stderr, RED"Wrong command of neonate\n"RESET);
        return;
    }
    if (strcmp(array[1], "-n") != 0)
    {
        fprintf(stderr, RED"Wrong command of neonate\n"RESET);
        return;
    }
    if (!numberchecker(array[2]))
    {
        fprintf(stderr, RED"No number found as time\n"RESET);
        return;
    }
    alrmtime = atoi(array[2]);
    if (alrmtime == 0)
    {
        enableRawMode();
        char ch;
        while (1)
        {
            if (kbhit())
            {
                if (read(STDIN_FILENO, &ch, 1)&&ch == 'x')
                {
                    break;
                }
            }
            else
            {
                char path[500];
                sprintf(path, "/proc/loadavg");
                FILE *fptr = fopen(path, "r");
                if (fptr == NULL)
                {
                    fprintf(stderr, RED "file didn't open \n" RESET);
                    error1();
                }
                char string[5000];
                fread(string, sizeof(char), 5000, fptr);
                char garb[100];
                pid_t pidno;
                printf("%d\n", pidno);

                sscanf(string, "%s %s %s %s %d", garb, garb, garb, garb, &pidno);
                printf("%d\n", pidno);
                fclose(fptr);
            }
        }
        disableRawMode();
        return;
    }
    enableRawMode();
    alarm(alrmtime);
    char ch;

    while (1)
    {
        if (read(STDIN_FILENO, &ch, 1))
        {
            if (ch == 'x')
            {
                alarmflag = 1;
                break;
            }
        }
    }
    disableRawMode();
}