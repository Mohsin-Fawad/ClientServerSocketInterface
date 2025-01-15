#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXSIZE 80
#define PORT 8080
#define SA struct sockaddr

void CliServComm(int sockfd) 
{
    char buffAr[MAXSIZE];
    int ind;

    while (1) {
        bzero(buffAr, sizeof(buffAr));
        printf("Enter the Msg : ");
        ind = 0;

        while ((buffAr[ind] = getchar()) != '\n') {
            ind++;
        }

        write(sockfd, buffAr, sizeof(buffAr));
        bzero(buffAr, sizeof(buffAr));
        read(sockfd, buffAr, sizeof(buffAr));
        printf("From Server : %s", buffAr);

        if ((strncmp(buffAr, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

int main()
{
    int cliSock;
    struct sockaddr_in servAddrStruc;

    cliSock = socket(AF_INET, SOCK_STREAM, 0);
    if (cliSock == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    bzero(&servAddrStruc, sizeof(servAddrStruc));
    servAddrStruc.sin_family = AF_INET;
    servAddrStruc.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddrStruc.sin_port = htons(PORT);

    if (connect(cliSock, (SA*)&servAddrStruc, sizeof(servAddrStruc)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    CliServComm(cliSock);
    close(cliSock);
    return 0;
}



