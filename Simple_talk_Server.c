#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SERVER_PORT 54321
#define MAX_PENDING 5
#define MAX_LINE 256

int main(){
    struct sockaddr_in server;
    char buf[MAX_LINE];
    int len;
    int sock, client_sock;

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(SERVER_PORT);

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Erro na criação do socket!");
        exit(1);
    }
    if((bind(sock, (struct sockaddr *) &server, sizeof(server))) < 0){
        perror("Erro no bind!");
        exit(1);  
    }
    printf("ouvindo\n");
    listen(sock, MAX_PENDING);
    printf("lendo\n");
    len = sizeof(server);
    while(1){
        if((client_sock = accept(sock, (struct sockaddr *) &server, &len)) < 0){
            perror("Erro na conecção!");
            exit(1); 
        }
        printf("ish\n");
        while(len = recv(client_sock, buf, sizeof(buf), 0)){
            fputs(buf, stdout);
        }
        close(client_sock);
    }

}