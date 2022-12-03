/*
    3) A seguir é apresentada versão serial de um programa para cálculo de todos os números primos até um determinado valor.
    Implemente uma versão com múltiplos processos colaborando para o cálculo dos números primos. Avalie o desempenho do
    seu programa com dois valores de entrada: 10.000.000 e 100.000.000. Ao faer a compração, não imprima o resultado na
    tela, pois a concorrência para realização de E/S tomará o programa muito mais lento e afetará a avaliação.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdbool.h>

#define SOCK_PATH "calc_primo"

int main(void)
{
    struct sockaddr_un server_sockaddr, peer_sock;
    char buf[256];
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(buf, 0, 256);

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SOCK_PATH);

    int len = sizeof(server_sockaddr);
    unlink(SOCK_PATH);

    int serverSocket = socket(AF_UNIX, SOCK_DGRAM, 0);
    bind(serverSocket, (struct sockaddr *)&server_sockaddr, len);

    int max;
    int countPrints = 0;
    printf("Aguardando o recebimento de dados...\n");
    do
    {
        recvfrom(serverSocket, buf, 256, 0, (struct sockaddr *)&peer_sock, &len);
        printf("O número %s é primo\n", buf);
    } while (true);
}