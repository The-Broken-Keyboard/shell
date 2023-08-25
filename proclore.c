#include "proclore.h"

void proclore(char *input)
{
    if (strcmp(input, "proclore") == 0)
    {
        int pid = getpid();
        char *path = (char *)malloc(sizeof(char) * 50);
        for (int i = 0; i < 50; i++)
            path[i] = '\0';
        sprintf(path, "/proc/%d/stat", pid);
        FILE *fptr = fopen(path, "r");
        if (fptr == NULL)
        {
            printf("file didn't open\n");
            return;
        }
        char buff[100];
        int count = 0;
        while (fscanf(fptr, "%s", buff))
        {
            count++;
            if (count == 1)
                printf("PID : %s\n", buff);
            if (count == 3){
                printf("Process Status : %s+\n", buff);

            }
            if (count == 5)
                printf("Process Group : %s\n", buff);
            if (count == 23)
            {
                printf("Virtual Memory : %s\n", buff);
                break;
            }
        }

        fclose(fptr);
        char executable[500];
        for (int i = 0; i < 500; i++)
            executable[i] = '\0';
        char exe[50];
        sprintf(exe, "/proc/%d/exe", pid);
        readlink(exe, executable, 499);
        printf("Executable Path : %s\n", executable);
        return;
    }
    char second[20];
    for (int i = 0; i < 20; i++)
    {
        second[i] = '\0';
    }
    int flag = 0;
    int pos = 0;
    int size = strlen(input);
    for (int i = 0; i < size; i++)
    {
        if (flag == 1)
        {
            second[pos++] = input[i];
        }
        if (input[i] == ' ')
            flag = 1;
    }
    int OGgroupid=getpgrp();
    second[pos] = '\0';
    int pid = atoi(second);
    char *path = (char *)malloc(sizeof(char) * 50);
    for (int i = 0; i < 50; i++)
        path[i] = '\0';
    sprintf(path, "/proc/%d/stat", pid);
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL)
    {
        printf("file didn't open\n");
        return;
    }
    char buff[100];
    int count = 0;
    char** resu=(char**)malloc(sizeof(char*)*10);
    for(int i=0;i<10;i++)
    resu[i]=(char*)malloc(sizeof(char)*100);
    for(int i=0;i<10;i++)
    resu[i][0]='\0';
    while (fscanf(fptr, "%s", buff))
    {
        count++;
        if (count == 1)
            catenate(resu[0],buff,0);
        if (count == 3){
           catenate(resu[1],buff,0);
        }
        if (count == 5)
           catenate(resu[2],buff,0);
        if (count == 23)
        {
            catenate(resu[3],buff,0);
            break;
        }
    }
     fclose(fptr);
    printf("Pid : %s\n",resu[0]);
    int gid=atoi(resu[2]);
    if(gid==OGgroupid)
    printf("Process Status : %s+\n",resu[1]);
    else{
        printf("Process Status : %s\n",resu[1]);
    }
    printf("Process Group : %s\n",resu[2]);
    printf("Virtual Memory : %s\n",resu[3]);
    char executable[500];
    for (int i = 0; i < 500; i++)
        executable[i] = '\0';
    char exe[50];
    sprintf(exe, "/proc/%d/exe", pid);
    readlink(exe, executable, 499);
    printf("Executable Path : %s\n", executable);
    return;
}