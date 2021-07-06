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
    FILE * file_descriptor;
    /**======================
     **      Variáveis
     *========================**/
    struct sockaddr_in server;
    char *host;
    char buf[MAX_LINE];
    int sock;
    int len;
    printf("%s", argv[2]);
    if( argc == 3) {
        host = argv[1];
        if((file_descriptor = fopen(argv[2], "r")) == NULL){
           fprintf(stderr, "Erro ao abrir o arquivo.\n");
           exit(1); 
        }
    }else{
        fprintf(stderr, "Usage: EXP1client IP_server file\n");
        exit(1);
    }

    /**======================
     **      Inicializa server
     *========================**/
    printf("Inicializando client...\n");
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(host);
    server.sin_port = htons(SERVER_PORT);
    
    /**======================
     **      Realiza a conexão
     *========================**/
    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror("Erro na criação do socket:");
        exit(1);
    }

    printf("Conectando ao servidor: %s:%d\n", host, SERVER_PORT);
    if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0){
        perror("Erro na conexão:");
        close(sock);
        exit(1);
    }
    printf("Conectado ao servidor: %s:%d com sucesso\n", host, SERVER_PORT);

    /**======================
     **      Troca de mensagem
     *========================**/
    printf("\nLendo mensagem do arquivo:\n");
    while ((fgets(buf, sizeof(buf), file_descriptor))) {
        buf[MAX_LINE - 1] = '\0';
        len = strlen(buf) + 1;
        printf("%s", buf);
        if(send(sock, buf, len, 0) < 0){
            perror("Erro ao enviar mensagem:");
            close(sock);
            exit(1);
        }
    }
    printf("Mensagem enviada com sucesso!\n");
    close(sock);
}