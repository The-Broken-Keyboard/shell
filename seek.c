#include "headers.h"
int finalresultpos;
char* dotRemoval(char*string, char* actualpath)
{
    char* result=(char*)malloc(sizeof(char)*((strlen(string)+strlen(actualpath))+1));
    for(int i=0;i<strlen(string)+strlen(actualpath)+1;i++)
    {
        result[i]='\0';
    }
    char temp[strlen(string)];
    int pos=0;
    for(int i=1;i<strlen(string);i++)
    temp[pos++]=string[i];
    temp[pos]='\0';
    catenate(result,actualpath,0);
    catenate(result,temp,0);
    return result;
}
int isexecutable(char *filename, char *path)
{
    struct stat buff;
    char filepath[100];
    for (int i = 0; i < 100; i++)
        filepath[i] = '\0';
    catenate(filepath, path, 0);
    catenate(filepath, "/", 0);
    catenate(filepath, filename, 0);
    // printf("%s\n", array[j]);
    stat(filepath, &buff);
    if(buff.st_mode & S_IXUSR)
    return 1;
    return 0;
}
int isdirectory2(char *path)
{
    struct stat buff;
    char filepath[100];
    for (int i = 0; i < 100; i++)
        filepath[i] = '\0';
    catenate(filepath, path, 0);
    // printf("%s\n", array[j]);
    stat(filepath, &buff);
    if(buff.st_mode & __S_IFDIR)
    return 1;
    return 0;
}
int isdirectory(char *filename, char *path)
{
    struct stat buff;
    char filepath[100];
    for (int i = 0; i < 100; i++)
        filepath[i] = '\0';
    catenate(filepath, path, 0);
    catenate(filepath, "/", 0);
    catenate(filepath, filename, 0);
    // printf("%s\n", array[j]);
    stat(filepath, &buff);
    switch (buff.st_mode & __S_IFMT)
    {
    case __S_IFDIR:
        return 1;
        break;
    default:
        return 0; // Unknown file
    }
    return 0;
}
void writefinalanswer(char **finalanswer, char **searchpath,int searchpathPos, char *filename)
{
    char path[1000];
    for (int i = 0; i < 1000; i++)
        path[i] = '\0';
    catenate(path,"/",0);
    for (int i = 1; i < searchpathPos; i++)
    {
        catenate(path, searchpath[i], 0);
        if (i != searchpathPos - 1)
        {
            catenate(path, "/", 0);
        }
    }
    finalanswer[finalresultpos][0] = '\0';
    catenate(finalanswer[finalresultpos],".",0);
    catenate(finalanswer[finalresultpos], path, 0);
    if(searchpathPos!=1)
    catenate(finalanswer[finalresultpos], "/", 0);
    catenate(finalanswer[finalresultpos], filename, 0);
    finalresultpos++;
    return;
}
void letsSearch(char **arr, char **finalresult, char **searchpath, int searchpathPos)
{
    char **array = (char **)malloc(sizeof(char *) * 500);
    for (int i = 0; i < 500; i++)
        array[i] = (char *)malloc(sizeof(char) * 100);
    int i = 0, j = 0, k = 0;
    DIR *dir;
    struct dirent *dent;
    char buffer[1000];
    for (int i = 0; i < 1000; i++)
        buffer[i] = '\0';
    char path[1000];
    for (int i = 0; i < 1000; i++)
        path[i] = '\0';
    for (int i = 0; i < searchpathPos; i++)
    {
        catenate(path, searchpath[i], 0);
        if (i != searchpathPos - 1)
        {
            catenate(path, "/", 0);
        }
    }
    // getcwd(path, 99);
    catenate(buffer, path, 0);
    dir = opendir(buffer); // this part
    if (dir != NULL)
    {
        while ((dent = readdir(dir)) != NULL)
        {
            //     printf("%s\n", dent->d_name);
            strcpy(array[i], dent->d_name);
            i++;
            k++;
        }
        closedir(dir);
    }
    else
    {
        printf("Directory didn't open\n");
        return;
    }
    sort((const char **)array, i);
    // for(int i=0;i<k;i++)
    // printf("%s\n",array[i]);
    // return;
    for (int i = 0; i < k; i++)
    {
        if (array[i][0] == '.')
            continue;
        if (isdirectory(array[i], path))
        {
            if (strstr(array[i], arr[4]) != NULL && strcmp(arr[1], "nothing") == 0)
                writefinalanswer(finalresult,searchpath,searchpathPos,array[i]);
            strcpy(searchpath[searchpathPos], array[i]);
            letsSearch(arr, finalresult, searchpath, searchpathPos + 1);
            searchpath[searchpathPos][0] = '\0';
        }
        else
        {
            if (strstr(array[i], arr[4]) != NULL && strcmp(arr[2], "nothing") == 0)
                writefinalanswer(finalresult,searchpath,searchpathPos,array[i]);
        }
    }
}
void seek(char *input)
{
    int z = 0;
    char **arr = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
        arr[i] = (char *)malloc(sizeof(char) * 100);
    for (int i = 0; i < 100; i++)
        strcpy(arr[i], "nothing");
    char t[100];
    char *token;
    char *ptr_out = NULL;
    char del[] = " \t\f\v\r\n";
    token = NULL;
    ptr_out = NULL;
    strcpy(t, input);
    token = __strtok_r(t, del, &ptr_out);
    z = 4;
    while (token != NULL)
    {
        if (strcmp(token, "seek") == 0)
            strcpy(arr[0], token);
        else if (strcmp(token, "-f") == 0)
            strcpy(arr[1], "-f");
        else if (strcmp(token, "-d") == 0)
            strcpy(arr[2], "-d");
        else if (strcmp(token, "-e") == 0)
        {
            strcpy(arr[3], "-e");
        }
        else if (strcmp(token, "-fe") == 0)
        {
            strcpy(arr[1], "-f");
            strcpy(arr[3], "-e");
        }
        else if (strcmp(token, "-de") == 0)
        {
            strcpy(arr[2], "-d");
            strcpy(arr[3], "-e");
        }
        else if (strcmp(token, "-ef") == 0)
        {
            strcpy(arr[1], "-f");
            strcpy(arr[3], "-e");
        }
        else if (strcmp(token, "-ed") == 0)
        {
            strcpy(arr[2], "-d");
            strcpy(arr[3], "-e");
        }
        else if (strcmp(token, "-df") == 0 || strcmp(token, "-fd") == 0 || strcmp(token, "-fde") == 0 || strcmp(token, "-fed") == 0)
        {
            printf("Invalid flags!\n");
            return;
        }
        else if (strcmp(token, "-dfe") == 0 || strcmp(token, "-def") == 0 || strcmp(token, "-efd") == 0 || strcmp(token, "-edf") == 0)
        {
            printf("Invalid flags!\n");
            return;
        }
        else
        {
            strcpy(arr[z++], token);
        }
        token = __strtok_r(NULL, del, &ptr_out);
    }
    if (strcmp(arr[5], "nothing") == 0)
        strcpy(arr[5], ".");
    char path[100];
    for (int i = 0; i < 100; i++)
        path[i] = '\0';
    if (arr[5][0] != '/')
    {
        if (arr[5][0] == '~')
        {
            catenate(path, shellpath, 0);
            char *result = tildaDothandler(arr[5]);
            if (result != NULL)
                catenate(path, result, 0);
        }
        else if (arr[5][0] == '.')
        {
            getcwd(path, 99);
            char *result = tildaDothandler(arr[5]);
            if (result != NULL)
                catenate(path, result, 0);
        }
        else
        {
            getcwd(path, 99);
            catenate(path, "/", 0);
            catenate(path, arr[5], 0);
        }
    }
    else
    {
        strcpy(path, arr[5]);
    }
    // printf("%s\n",path);
    strcpy(arr[5], path);
    char **searchpath = (char **)malloc(sizeof(char *) * 500);
    for (int i = 0; i < 500; i++)
    {
        searchpath[i] = (char *)malloc(sizeof(char) * 500);
        searchpath[i][0] = '\0';
    }
    strcpy(searchpath[0], arr[5]);
    char **finalresult = (char **)malloc(sizeof(char *) * 500);
    for (int i = 0; i < 500; i++)
    {
        finalresult[i] = (char *)malloc(sizeof(char) * 500);
        finalresult[i][0] = '\0';
    }
    finalresultpos = 0;
    letsSearch(arr, finalresult, searchpath, 1);
    // printf("%d\n", finalresultpos);
    if (finalresultpos == 0)
    {
        printf("No match found\n");
        return;
    }
    for (int i = 0; i < finalresultpos; i++){
        char* result=dotRemoval(finalresult[i],path);
        if(isdirectory2(result))
        printf(BLUE"%s\n"RESET, finalresult[i]);
        else{
            printf(GREEN"%s\n"RESET,finalresult[i]);
        }
    }
    if (finalresultpos == 1 && strcmp(arr[3], "-e") == 0)
    {
        char* result=dotRemoval(finalresult[0],path);
        if (isdirectory2(result))
            chdir(result);
        else
        {
            FILE *fptr = fopen(result, "r");
            if (fptr == NULL)
            {
                printf("Missing permission for task!\n");
                return;
            }
            char buffer[50000];
            fread(buffer, sizeof(char), 49999, fptr);
                printf(WHITE"%s\n"RESET, buffer);
            fclose(fptr);
        }
    }

    return;
}