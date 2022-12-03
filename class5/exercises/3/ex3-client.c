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
#include <math.h>

#define SERVER_PATH "calc_primo"

int verifica_se_primo(long int numero)
{
    long int ant;
    for (ant = 2; ant <= (long int)sqrt(numero); ant++)
    {
        if (numero % ant == 0)
            return 0;
    }
    if (ant * ant >= numero)
        return 1;
}

int main(void)
{
    int max;
    printf("Informe um número para identificarmos quantos números menores que ele são primos:\n");
    scanf("%d", &max);

    struct sockaddr_un remote;
    char buf[256];
    memset(&remote, 0, sizeof(struct sockaddr_un));

    int client_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SERVER_PATH);

    for (int i = 0; i <= max; i++)
    {
        if (verifica_se_primo(i) == 1)
        {
            char data[20];
            sprintf(data, "%d", i);
            strcpy(buf, data);
            sendto(client_socket, buf, strlen(buf), 0, (struct sockaddr *)&remote, sizeof(remote));
        }
    }

    close(client_socket);
    return 0;
}