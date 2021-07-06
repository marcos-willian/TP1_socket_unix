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
    /**======================
     **      Variáveis
     *========================**/
    struct sockaddr_in server;
    char *host;
    char buf[MAX_LINE];
    int sock;
    int len;

   
    if( argc == 2) {
        host = argv[1];
    }else{
        fprintf(stderr, "Usage: STclient IP_server\n");
        exit(1);
    }

    printf("Inicializando client...\n");
     /**======================
     **      Inicializa server
     *========================**/
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(host);
    server.sin_port = htons(SERVER_PORT);
    
    /**======================
     **      Realiza a conexão
     *========================**/
    if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Erro na criação do socket:");
        exit(1);
    }

    /**======================
     **      Troca de mensagem
     *========================**/
    printf("Enviando menssagem ao servidor: %s:%d\n", host, SERVER_PORT);
    printf("\nEscreva uma mensagem:\n");
    while ((fgets(buf, sizeof(buf), stdin)) && strcmp(buf,"quit\n")){
        buf[MAX_LINE - 1] = '\0';
        len = strlen(buf) + 1;
        if(sendto(sock, (char *)buf, len, 0, (const struct sockaddr *) &server,	sizeof(server)) < 0){
            perror("Erro ao enviar mensagem:");
            close(sock);
            exit(1);
        }
        printf("Mensagem enviada com sucesso!\n");
        printf("\nEscreva uma mensagem:\n");
    }
    close(sock);
}