#include "./include/headers.h"
char cwd[128];

void printfinished()
{
    if (recordHead->next == recordHead)
        return;
    struct recordOfCommands *temp = recordHead->next;
    struct recordOfCommands *next;
    while (temp != recordHead)
    {
        next = temp->next;
        char path[500];
        sprintf(path,"/proc/%d/stat",temp->pid);
        FILE *fptr = fopen(path, "r");
        if(fptr==NULL){
        fprintf(stderr,RED"file didn't open\n"RESET);
        error1();
        }
        char string[5000];
        fread(string, sizeof(char), 5000, fptr);
        char garb[100];
        char status;
        sscanf(string,"%s %s %c",garb,garb,&status);
        if(status=='Z')
        {
            printf("%s [%d] exited normally\n",temp->commandname,temp->pid);
            removenodeFromRecordlist(temp);
        }
        temp = next;
    }
}
char *promptmodifier(char *str1)
{
    long long size = strlen(cwd);
    long long size2 = strlen(str1);
    long long pos = 0;
    char *result = (char *)malloc(sizeof(char) * ((size2 - size) + 3));
    result[pos++] = '~';
    for (long long i = size; i < strlen(str1); i++)
    {
        result[pos++] = str1[i];
    }
    result[pos] = '\0';
    return result;
}
void x()
{
    char hostbuffer[256];
    int hostname;
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    if (hostname == -1)
    {
        error1();
    }
    char *user;
    user = getlogin();
    char path[128];
    getcwd(path, 128);
    strcpy(cwd, path);
    strcpy(shellpath,path);
    return;
}

void prompt()
{
    // Do not hardcode the prmopt
    // struct utsname buffer;
    // if(uname(&buffer)<0)
    // error1();
    printfinished();
    char hostbuffer[256];
    int hostname;
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    if (hostname == -1)
    {
        error1();
    }
    // struct passwd *p;
    // uid_t uid = 1;
    // if((p=getpwuid(uid))== NULL)
    // error1();
    char *user;
    user = getlogin();
    char path[128];
    getcwd(path, 128);
    if (strstr(path, cwd) == path)
    {
        if (flag == 0){
            printf(GREEN"<%s"RESET, user);
            printf(BLUE"@%s:%s>"RESET,hostbuffer,promptmodifier(path));
        }
            

        else
        {
            printf(GREEN"<%s"RESET, user);
            printf(BLUE"@%s:%s "RESET,hostbuffer,promptmodifier(path));
            printf(WHITE"%s %lds>"RESET,commandsname,timetaken);
            flag = 0;
            timetaken = 0;
            free(commandsname);
        }
    }
    else
    {
        if (flag == 0){
            printf(GREEN"<%s"RESET, user);
            printf(BLUE"@%s:%s>"RESET,hostbuffer,path);
        }
        else
        {
            printf(GREEN"<%s"RESET, user);
            printf(BLUE"@%s:%s "RESET,hostbuffer,path);
            printf(WHITE"%s %lds>"RESET,commandsname,timetaken);
            flag = 0;
            timetaken = 0;
            free(commandsname);
        }
        // printf("<Everything is a file> ");
    }
}
