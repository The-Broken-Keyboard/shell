#include "headers.h"
int pasteventsFlag;
void catenate(char *result, char *token, int spaceflag)
{
    int pos = strlen(result);
    int size = strlen(token);
    if (spaceflag == 1)
        result[pos++] = ' ';
    for (int i = 0; i < size; i++)
    {
        result[pos++] = token[i];
    }
    result[pos] = '\0';
}
char *handlePastEvents(char *input)
{
    int pF = 0;
    int pEF = 0;
    char **array = (char **)malloc(sizeof(char *) * 1000);
    for (int i = 0; i < 1000; i++)
        array[i] = (char *)malloc(sizeof(char) * 500);
    char *temp = (char *)malloc(sizeof(char) * 4096);
    strcpy(temp, input);
    char *token;
    char *ptr_out = NULL;
    char del[] = " \t\f\v\r\n";
    token = NULL;
    ptr_out = NULL;
    token = __strtok_r(temp, del, &ptr_out);
    int i = 0;
    while (token != NULL)
    {
        strcpy(array[i++], token);
        token = __strtok_r(NULL, del, &ptr_out);
    }
    char *result = (char *)malloc(sizeof(char) * 4096);
    result[0] = '\0';
    for (int j = 0; j < i; j++)
    {
        if (j == 0)
            catenate(result, array[j], 0);
        else
            catenate(result, array[j], 1);
    }
    destroystringlist(array, 1000);
    return result;
}
char *pasteventsExecute(char *input)
{
    int size = strlen(input);
    int lineno = input[size - 1] - '0';
    char filepath[500];
    filepath[0] = '\0';
    catenate(filepath, shellpath, 0);
    catenate(filepath, "/pastevents.bin", 0);
    FILE *fptr = fopen(filepath, "r");
    char *buff = (char *)malloc(sizeof(char) * 4096);
    int count = 0;
    while (fread(buff, sizeof(char), 4096, fptr))
        count++;
    fseek(fptr, 0, SEEK_SET);
    if (count < lineno)
    {
        printf("NO pastevent exists\n");
        return NULL;
    }
    int finallineno = count - lineno + 1;
    count = 0;
    char *buff2 = (char *)malloc(sizeof(char) * 4096);
    while (fread(buff2, sizeof(char), 4096, fptr))
    {
        count++;
        if (count == finallineno)
            break;
    }
    fclose(fptr);
    return buff2;
}
void pasteventsExecuteExtraction(char *input)
{
    struct commandnode *result = parse(input);
    int i = 0;
    pasteventsFlag = 0;
    char *pasteventfinalresult = (char *)malloc(sizeof(char) * 4096);
    pasteventfinalresult[0] = '\0';
    struct commandnode *next = result->next;
    time_t time1 = time(NULL);
    int count = 0;
    while (next != result)
    {
        char *token = commandName(next->command);
        if (validtoken(token) == 0)
        {
            next = next->next;
            continue;
        }
        time_t time1 = time(NULL);
        if (strcmp(token, "warp") == 0)
        {
            warp(next->command);
        }
        else
        {
            if (next->bg)
                execVP(next->command, 1);
            else
                execVP(next->command, 0);
        }
        next = next->next;
    }
}

void pasteventsPurge()
{
    char filepath[500];
    filepath[0] = '\0';
    catenate(filepath, shellpath, 0);
    catenate(filepath, "/pastevents.bin", 0);
    FILE *fptr = fopen(filepath, "w");
    fclose(fptr);
    return;
}
void pastevents()
{
    char filepath[500];
    filepath[0] = '\0';
    catenate(filepath, shellpath, 0);
    catenate(filepath, "/pastevents.bin", 0);
    FILE *fptr = fopen(filepath, "r");
    char buff[4096];
    int count = 0;
    if (fptr == NULL)
    {
        printf("NO pastevents exist!\n");
        return;
    }
    while (fread(buff, sizeof(char), 4096, fptr))
    {
        count++;
        printf("%s\n", buff);
    }
    if (count == 0)
    {
        printf("NO pastevents exist!\n");
    }
    fclose(fptr);
    return;
}
