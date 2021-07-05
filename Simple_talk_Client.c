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
#define MAX_LINE 256

int main(int argc, char * argv[]){
    FILE *fp;
    struct sockaddr_in server;
    char *host;
    char buf[MAX_LINE];
    int sock;
    int len;

    if( argc == 2) {
        host = argv[1];
    }else{
        fprintf(stderr, "usage: Simple_talk_Client IP_server\n");
        exit(1);
    }
    
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY/*inet_addr(host)*/;
    server.sin_port = htons(SERVER_PORT);
    
    if((sock = socket(AF_INET, SOCK_STREAM, 0) < 0)){
        perror("Erro na criação do socket!");
        exit(1);
    }

    if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0){
        perror("Erro na conecção!");
        close(sock);
        exit(1);
    }

    while (fgets(buf, sizeof(buf), stdin)){
        buf[MAX_LINE - 1] = '\0';
        len = strlen(buf) + 1;
        send(sock, buf, len, 0);
    }
}