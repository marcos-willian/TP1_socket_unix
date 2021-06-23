#include <errno.h> 
//#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#define SERVER_PORT 53421
#define BUFFERSIZE 100
int main(int argc, char const *argv[])
{
    int sock_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_descriptor < 0){
        perror("Socket erro: ");
        exit(1);
    }
    struct sockaddr_in  client;
    client.sin_family = AF_INET;
    client.sin_port = 0;
    client.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock_descriptor,(struct sockaddr *) &client,sizeof(client))<0)
    { 
        perror("Falha no bind!\n");
        exit(1);
    }
    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT); 
    server.sin_addr.s_addr = inet_addr("150.164.226.33");
    int server_len, count, bytecount = 100;
    char buffer[BUFFERSIZE];
    scanf("%s", buffer);
    count = sendto(sock_descriptor, buffer, bytecount, 0, (struct sockaddr *) &server,sizeof(server)); 
    server_len = sizeof(server);
    count = recvfrom(sock_descriptor, buffer, BUFFERSIZE, 0, (struct sockaddr *) &server, &server_len);
    printf("%s", buffer);
    system("PAUSE");
}
