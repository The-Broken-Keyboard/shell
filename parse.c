#include "./include/headers.h"
int waste(char*string)
{
    int size=strlen(string);
    for(int i=0;i<size;i++)
    {
        if(string[i]=='\n'||string[i]==' '||string[i]=='\t'||string[i]=='\v'||string[i]=='\f'||string[i]=='\r'||string[i]==';'||string[i]=='&')
        continue;
        else
        return 0;
    }
    return 1;
}
char *trim(char *token)
{
    int size=strlen(token);
    char *result = (char *)malloc(sizeof(char) *5000);
    result[0] = '\0';
    for (int i = 1; i < size + 1; i++)
        result[i] = '\0';
    int pos = 0;
    for (int i = 0; i < size; i++)
    {
        if ((token[i] == ' ' || token[i] == '\n' || token[i] == '\t' || token[i] == '\r' || token[i] == '\v' || token[i] == '\f') && pos == 0)
            continue;
        else
        {
            result[pos++] = token[i];
        }
    }
    result[pos] = '\0';
    while(result[pos-1]==' '||result[pos-1]=='\t'||result[pos-1]=='\r'||result[pos-1]=='\v'||result[pos-1]=='\f')
    {
        pos--;
        result[pos]='\0';
    }
    return result;
}
struct commandnode *parse(char *string)
{
    if(waste(string))
    return NULL;
    char *temp = (char *)malloc(sizeof(char) * 500);
    strcpy(temp, string);
    char *token;
    char *ptr_in = NULL;
    char del1[] = ";&\n";
    int pos = 0;
    int cnt = 0;
    token = __strtok_r(temp, del1, &ptr_in);
    if(token==NULL)
    return NULL;
    char*tempu=(char*)malloc(sizeof(char)*1000);
    tempu[0]='\0';
    strcpy(tempu,token);
    char* result1=trim(tempu);
    struct commandnode *head = (struct commandnode *)malloc(sizeof(struct commandnode));
    head->next = NULL;
    head->prev = NULL;
    struct commandnode *last;
    // char *result1 = trim(token);
    if (strlen(result1) > 0)
    {
        struct commandnode *new = (struct commandnode *)malloc(sizeof(struct commandnode));
        strcpy(new->command, result1);
        new->bg = false;
        if (string[(int)(ptr_in - temp) - 1] == '&')
            new->bg = true;
        else
            new->bg = false;
        last = new;
        last->next = NULL;
        last->prev = head;
        head->next = new;
    }
    token = __strtok_r(NULL, del1, &ptr_in);
    while (token != NULL)
    {

        // printf("%ld\n",strlen(token));
        char *result = trim(token);
        if (strlen(result) == 0)
        {
            token = __strtok_r(NULL, del1, &ptr_in);
            continue;
        }
        struct commandnode *tempo = (struct commandnode *)malloc(sizeof(struct commandnode));
        tempo->bg = false;
        if (string[(int)(ptr_in - temp) - 1] == '&')
            tempo->bg = true;
        else
            tempo->bg = false;
        strcpy(tempo->command, result);
        last->next = tempo;
        tempo->prev = last;
        last = tempo;
        token = __strtok_r(NULL, del1, &ptr_in);
    }
    last->next = head;
    head->prev = last;
    return head;
}