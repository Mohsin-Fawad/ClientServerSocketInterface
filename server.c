#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXSIZE 80
#define PORT 8080
#define SA struct sockaddr

void CliServComm(int connSock) 
{ 
    char buffAr[MAXSIZE];         
    int ind;                  
    
    while (1) { 
        bzero(buffAr, MAXSIZE);    
        read(connSock, buffAr, sizeof(buffAr));  
        printf("From client: %s", buffAr); 
        bzero(buffAr, MAXSIZE);    
        ind = 0;               

        printf("To Client:");
        while ((buffAr[ind] = getchar()) != '\n'){   
            ind++;
        } 
        write(connSock, buffAr, sizeof(buffAr));  
        if (strncmp("exit", buffAr, 4) == 0) {  
            printf("Server Exit...\n");       
            break;                            
        } 
    } 
}

int main() 
{ 
    int servSock, connSock, lenCAStruc;          
    struct sockaddr_in servAddrStruc, cliAddrStruc; 
  
    servSock = socket(AF_INET, SOCK_STREAM, 0);  
    if (servSock == -1) {                    
        printf("socket creation failed...\n");  
        exit(0);                           
    } 
    else
        printf("Socket successfully created..\n"); 
    
    bzero(&servAddrStruc, sizeof(servAddrStruc));   
    servAddrStruc.sin_family = AF_INET;       
    servAddrStruc.sin_addr.s_addr = htonl(INADDR_ANY);  
    servAddrStruc.sin_port = htons(PORT);     

    if ((bind(servSock, (SA*)&servAddrStruc, sizeof(servAddrStruc))) != 0) {  
        printf("socket bind failed...\n");  
        exit(0);                           
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    if ((listen(servSock, 5)) != 0) {     
        printf("Listen failed...\n");    
        exit(0);                        
    } 
    else
        printf("Server listening..\n");  
    
    lenCAStruc = sizeof(cliAddrStruc);  

    connSock = accept(servSock, (SA*)&cliAddrStruc, &lenCAStruc);  
    if (connSock < 0) {  
        printf("server accept failed...\n");   
        exit(0);                             
    } 
    else
        printf("server accept the client...\n");  
  
    CliServComm(connSock);  
    close(servSock);  
    return 0;
}





