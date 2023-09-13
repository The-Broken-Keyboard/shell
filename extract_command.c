#include "./include/headers.h"

time_t timetaken;
char *commandsname;
int flag;
int isPipeOrRedirection(char* input)
{
    int size=strlen(input);
    char* temp=(char*)malloc(sizeof(char)*(size+2));
    temp[0]='\0';
    catenate(temp,input,0);
    for(int i=0;i<size;i++)
    {
        if(temp[i]=='|'||temp[i]=='<'||temp[i]=='>')
        {
            return 1;
        }
    }
    return 0;
}
char *commandName(char *command)
{
    char **array = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
        array[i] = (char *)malloc(sizeof(char) * 100);
    // char t[100];
    char *t = (char *)malloc(sizeof(char) * 100);
    char *token;
    char *ptr_out = NULL;
    char del[] = " \t\f\v\r\n";
    token = NULL;
    ptr_out = NULL;
    strcpy(t, command);
    token = __strtok_r(t, del, &ptr_out);
    char *result = (char *)malloc(sizeof(char) * 100);
    if (token != NULL)
    {
        strcpy(result, token);
        destroystringlist(array, 100);
        return result;
    }
    destroystringlist(array, 100);
    free(result);
    return NULL;
}
int iswarp(char *token)
{
    if (strcmp(token, "warp") == 0)
        return 1;
    return 0;
}
int validtoken(char *token)
{
    if (token == NULL)
        return 0;
    return 1;
}
int commandExtraction(struct commandnode *result)
{
    int i = 0;
    pasteventsFlag = 0;
    char *pasteventfinalresult = (char *)malloc(sizeof(char) * 4096);
    pasteventfinalresult[0] = '\0';
    struct commandnode *next = result->next;
    time_t time1 = time(NULL);
    int count = 0;
    while (next != result)
    {
        char *result = spaceOrganiser(next->command);
        if(strcmp("exit",trim(result))==0)
        {
            return -1;
        }
        if(isPipeOrRedirection(result))
        {
            result=Piping(result,0,STDOUT_FILENO,STDIN_FILENO);
            if(pasteventsFlag==0)
            {
                if(count==0)
                {
                    catenate(pasteventfinalresult,result,0);
                    count++;
                }
                else
                catenate(pasteventfinalresult,result,1);

                catenate(pasteventfinalresult,";",1);
            }
            next=next->next;
            continue;
        }
        if (strcmp(result, "pastevents") == 0 || strcmp(result, "pastevents purge") == 0)
            pasteventsFlag = 1;
        else if (strstr(result, "pastevents execute") == result)
        {
            // handle pastevents execute
            result = pasteventsExecute(result);
            if (result == NULL)
            {
                next = next->next;
                continue;
            }
            if(pasteventsFlag==0)
            {
                if(count==0)
                {
                    catenate(pasteventfinalresult,result,0);
                    count++;
                }
                else
                catenate(pasteventfinalresult,result,1);
            }
            pasteventsExecuteExtraction(result);
            next=next->next;
            continue;
        }
        

        if(strcmp(result,"pastevents purge")==0)
        {
            pasteventsPurge();
            next=next->next;
            continue;
        }
        else if(strcmp(result,"pastevents")==0)
        {
            pastevents();
            next=next->next;
            continue;
        }
        if (pasteventsFlag == 0)
        {
            if (count == 0)
            {
                catenate(pasteventfinalresult, result, 0);
                count++;
            }
            else
            {
                catenate(pasteventfinalresult, result, 1);
            }
            if (next->bg)
                catenate(pasteventfinalresult, "&", 1);
            else
                catenate(pasteventfinalresult, ";", 1);
        }

        if(strstr(result,"proclore")==result)
        {
            proclore(result);
            next=next->next;
            continue;
        }
        if(strstr(result,"peek")==result)
        {
            peek(result);
            next=next->next;
            continue;
        }
        if(strstr(result,"seek")==result)
        {
            seek(result);
            next=next->next;
            continue;
        }
        if(strstr(result,"ping")==result)
        {
            png(result);
            next=next->next;
            continue;
        }
        if(strstr(result,"fg")==result)
        {
            fg(result);
            next=next->next;
            continue;
        }
        if(strstr(result,"bg")==result)
        {
            bg(result);
            next=next->next;
            continue;
        }
        if(strstr(result,"iMan")!=NULL)
        {
            iman(result);
            next=next->next;
            continue;
        }
        if(strstr(result,"neonate")!=NULL)
        {
            neonate(result);
            next=next->next;
            continue;
        }
        if(strcmp(result,"activities")==0)
        {
            activities();
            next=next->next;
            continue;
        }
        // printf("%s\n",next->command);
        char *token = commandName(result);
        if (validtoken(token) == 0)
        {
            next = next->next;
            continue;
        }
        if (strcmp(token, "warp") == 0)
        {
            warp(result);
        }
        else
        {
            if (next->bg)
                execVP(result, 1);
            else
                execVP(result, 0);
        }
        next = next->next;
    }
    time_t time2 = time(NULL);
    // printf("%ld %ld\n",time1,time2);
    timetaken = 0;
    flag = 0;
    timetaken = time2 - time1;
    if (timetaken > 2)
    {
        flag = 1;
        next = result->next;
        int size;
        char *comname = (char *)malloc(sizeof(char) * 500);
        strcpy(comname, ":");
        while (next != result)
        {
            char *token = commandName(next->command);
            if (validtoken(token) == 1 && strstr(comname, token) == NULL && next->bg == 0)
            {
                strcat(comname, token);
                strcat(comname, ":");
                free(token);
            }
            next = next->next;
        }
        commandsname = comname;
    }
    if (pasteventsFlag == 0)
    {
        char filepath[500];
        filepath[0]='\0';
        catenate(filepath,shellpath,0);
        catenate(filepath,"/pastevents.bin",0);
        FILE *fptr = fopen(filepath, "r");
        if (fptr != NULL)
        {
            char *buff = (char *)malloc(sizeof(char) * 4096);
            int count = 0;
            while (fread(buff, sizeof(char), 4096, fptr))
                count++;
            fseek(fptr, 0, SEEK_SET);
            int finallineno = count;
            count = 0;
            char *buff2 = (char *)malloc(sizeof(char) * 4096);
            while (fread(buff2, sizeof(char), 4096, fptr))
            {
                count++;
                if (count == finallineno)
                    break;
            }
            if (strcmp(buff2, pasteventfinalresult) == 0)
            {
                fclose(fptr);
                return 0;
            }
            fclose(fptr);
        }
        FILE *fptr2 = fopen(filepath, "a");
        if(fptr2==NULL)
        {
            fprintf(stderr,RED"Pastevents file error!\n"RESET);
            return 0;
        }
        fwrite(pasteventfinalresult, sizeof(char), 4096, fptr2);
        fclose(fptr2);
    }

    return 0;
}