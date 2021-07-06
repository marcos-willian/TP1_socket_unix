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
#define SERVER_IP INADDR_ANY
#define MAX_PENDING 1
#define MAX_LINE 256

int main(){
    printf("Inicializando servidor...\n");
    /**======================
     **      Variáveis
     *========================**/
    struct sockaddr_in server, client_addr;
    char buf[MAX_LINE];
    int len, count, sock, client_sock;

    /**======================
     **      Inicializa servidor
     *========================**/
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = SERVER_IP; 
    server.sin_port = htons(SERVER_PORT);

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Erro na criação do socket:");
        exit(1);
    }
    if((bind(sock, (struct sockaddr *) &server, sizeof(server))) < 0){
        perror("Erro no bind:");
        exit(1);  
    }
    printf("Servidor: %s:%d  inicializado com sucesso\n",  inet_ntoa(server.sin_addr), SERVER_PORT);
    /**======================
     **      Interação com o client
     *========================**/
    listen(sock, MAX_PENDING);
    while(1){
        printf("\nAguardando conexão do client\n");
        len = sizeof(client_addr);
        if((client_sock = accept(sock, (struct sockaddr *) &client_addr, &len)) < 0){
            perror("Erro na conexão com o client:");
            exit(1); 
        }
        printf("Client conectado: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        while(count = recv(client_sock, buf, sizeof(buf), 0)){
            if(count < 0){
                perror("Erro ao receber mensagem:");
                close(sock);
                exit(1); 
            }
            buf[count] = '\0';
            printf("Cliente: %s", buf);
            printf("Server: ");
            fgets(buf, sizeof(buf), stdin);
            buf[MAX_LINE - 1] = '\0';
            count = strlen(buf) + 1;
            if(send(client_sock, buf, count, 0) < 0){
                perror("Erro ao enviar mensagem:");
                close(sock);
                exit(1);
            }
        }
        printf("Client desconectado\n");
        close(client_sock);
    }
    close(sock);

}