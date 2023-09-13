#include "./include/headers.h"

void iman(char *string)
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
    if (strcmp(array[0], "iMan") != 0)
    {
        fprintf(stderr,RED"Wrong command involving iMan\n"RESET);
        return;
    }

    char arg[500];
    arg[0] = '\0';
    catenate(arg, "man.he.net", 0);
    char ip[100];
    struct hostent *h;
    struct in_addr **list;
    if ((h = gethostbyname(arg)) == NULL)
    {
        herror("gethostbyname error");
        return;
    }
    list = (struct in_addr **)h->h_addr_list;
    for (int i = 0; list[i] != NULL; i++)
    {
        strcpy(ip, inet_ntoa(*list[0]));
        break;
    }
    char secondHalf[500];
    char request[1000];
    struct sockaddr_in serveraddr;
    int port = 80;
    secondHalf[0] = '\0';
    char commandname[500];
    // scanf("%s", commandname);
    commandname[0] = '\0';
    catenate(commandname, array[1], 0);
    catenate(secondHalf, "/?topic=", 0);
    catenate(secondHalf, commandname, 0);
    catenate(secondHalf, "&section=all", 0);
    int tcpSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcpSocket < 0)
        fprintf(stderr,RED"\nError opening socket"RESET);
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    serveraddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &(serveraddr.sin_addr));

    if (connect(tcpSocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
        fprintf(stderr,RED"\nError Connecting"RESET);

    bzero(request, 1000);

    snprintf(request, sizeof(request), "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", secondHalf, arg);

    if (send(tcpSocket, request, strlen(request), 0) < 0)
        fprintf(stderr,RED"Error with send()"RESET);

    bzero(request, 1000);
    int recvflag = 0;
    while (recv(tcpSocket, request, 999, 0) > 0)
    {
        if (strstr(request,"NAME\n") != NULL)
            printf(WHITE"\n%s"RESET, strstr(request, "NAME\n"));
        else
        recvflag = 1;
        break;
    }
    bzero(request, 1000);
    while (recv(tcpSocket, request, 999, 0) > 0 && recvflag==0)
    {
        int flag = 0;
        if (request != NULL)
        {
            for (int i = 0; i < strlen(request); i++)
            {
                if (request[i] == '<')
                {
                    flag = 1;
                }
                else if (request[i] == '>' && flag == 1)
                {
                    flag = 0;
                }
                else
                {
                    if (flag == 0)
                    {
                        printf(WHITE"%c"RESET, request[i]);
                    }
                }
            }
        }
        else{
            recvflag=1;
        }
    }
    if (recvflag == 1)
    {
        fprintf(stderr, RED"No such page found!\n"RESET);
        return;
    }
    printf("\n");
    close(tcpSocket);

    return;
}