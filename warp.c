#include "./include/headers.h"

char originalshell[500];
char previouspath[500];
char currentpath[500];
int prevpathFlag = 0;
void originalpath()
{
    char path[128];
    getcwd(path, 128);
    strcpy(originalshell, path);
    return;
}
//hello
char *replace(char *token)
{
    char *result = (char *)malloc(sizeof(char) * 500);
    int size = strlen(token);
    int pos = 0;
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
            result[pos++] = '.';
        else
            result[pos++] = token[i];
    }
    result[pos] = '\0';
    return result;
}
int gotoshell(char *token)
{

    chdir(originalshell);
    int t = chdir(replace(token));
    if (t == -1)
    {
        fprintf(stderr,RED"Invalid directory or path\n"RESET);
        error1();
        return -1;
    }
    return 0;
}
int minussign(char *token)
{
    char temp[500];
    int size = strlen(token);

    if (strcmp(token, "-") == 0)
    {
        strcpy(temp, currentpath);
        strcpy(currentpath, previouspath);
        strcpy(previouspath, temp);
    }
    else
    {
        fprintf(stderr,RED"Invalid path detected including '-'\n"RESET);
        return -1;
    }

    chdir(currentpath);
    return 0;
}
int warp(char *string)
{
    int flag = 0;
    char temp[100];
    strcpy(temp, string);
    char *token;
    char delimeter[] = " \n\t\f\v\r";
    char *ptr_in = NULL;
    token = __strtok_r(temp, delimeter, &ptr_in);
    getcwd(currentpath, sizeof(currentpath));
    while (token != NULL)
    {
        if (strcmp(token, "warp") == 0)
        {
            token = __strtok_r(NULL, delimeter, &ptr_in);
            continue;
        }
        else if (strstr(token, "~") == token)
        {
            getcwd(currentpath, sizeof(currentpath));
            int ret = gotoshell(token);
            if (ret == -1)
            {
                chdir(currentpath);
                flag = 1;
                break;
            }
            else
            {
                strcpy(previouspath, currentpath);
                prevpathFlag = 1;
                getcwd(currentpath, sizeof(currentpath));
                printf("%s\n", currentpath);
            }
            flag = 1;
            // prompt();
        }
        else if (strstr(token, "-") == token)
        {
            if (prevpathFlag == 0)
            {
                printf(YELLOW"There is no previous directory to jump\n"RESET);
                flag = 1;
                return -1;
            }
            getcwd(currentpath, sizeof(currentpath));
            char temp[500];
            strcpy(temp, previouspath);
            int ret = minussign(token);
            if (ret == -1)
            {
                strcpy(previouspath, temp);
                flag = 1;
                return -1;
            }
            else
            {
                getcwd(currentpath, sizeof(currentpath));
                printf("%s\n", currentpath);
            }
            // printf("\n");
            // prompt();
            flag = 1;
        }
        else
        {
            getcwd(currentpath, sizeof(currentpath));
            int check = chdir(token);
            if (check == -1)
            {
                fprintf(stderr,RED"Invalid directory or path\n"RESET);
                error1();
                flag = 1;
                return -1;
            }
            else
            {
                strcpy(previouspath, currentpath);
                prevpathFlag = 1;
                getcwd(currentpath, sizeof(currentpath));
                printf("%s\n", currentpath);
            }
            flag = 1;
            // printf("\n");
            // prompt();
        }
        token = __strtok_r(NULL, delimeter, &ptr_in);
    }
    if (flag == 0)
    {
        getcwd(previouspath, sizeof(previouspath));
        chdir(originalshell);
        printf("%s\n", originalshell);
    }
    return 0;
}