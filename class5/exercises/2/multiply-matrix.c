/*
    2) Multiplique duas matrizes, sendo que cada matriz é criada por processos diferentes. O cálculo da multiplicação pode ser
    realizado  em qualquer um dos processos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "element.h"

#define SOCK_PATH "multiply_matrix"
#define MATRIX_LEN 9

// Função para multiplicar os valores para a matriz m3. Se nas posições informadas já existir valor para m1 e m2, então podemos multiplicar e informar na m3;
void tryMultiply(int m1[3][3], int m2[3][3], int m3[3][3], int row, int col, int *quantityFilled)
{
    int m1Val = m1[row][col];
    int m2Val = m2[row][col];

    if (m1Val > 0 && m2Val > 0)
    {
        m3[row][col] = m1Val * m2Val;
        (*quantityFilled)++;
    }
}

void printMatrix(int m3[3][3], int matrix)
{
    char print[256];
    for (int row = 0; row < 3; row++)
    {
        char buf[256];
        sprintf(buf, "| %d %d %d |\n", m3[row][0], m3[row][1], m3[row][2]);
        strcat(print, buf);
    }

    printf("Matrix %d is:\n%s", matrix, print);
}

// Função para verificar se toda a matriz já foi preenchida.
bool isFilled(int quantityFilled)
{
    return quantityFilled == MATRIX_LEN;
}

int main()
{
    // Contador para controlar se a matriz já foi totalmente preenchida.
    int quantityFilled = 0;
    int m1[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int m2[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int m3[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    struct sockaddr_un server_sockaddr, peer_sock;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SOCK_PATH);

    int len = sizeof(server_sockaddr);
    unlink(SOCK_PATH);

    int serverSocket = socket(AF_UNIX, SOCK_DGRAM, 0);
    bind(serverSocket, (struct sockaddr *)&server_sockaddr, len);

    while (!isFilled(quantityFilled))
    {
        Element data;
        recvfrom(serverSocket, &data, sizeof(struct Element *), 0, (struct sockaddr *)&peer_sock, &len);

        switch (data.id)
        {
        case 1:
            m1[data.row][data.col] = data.value;
            break;
        case 2:
            m2[data.row][data.col] = data.value;
            break;
        default:
            break;
        }

        tryMultiply(m1, m2, m3, data.row, data.col, &quantityFilled);
    }

    printMatrix(m3, 3);
    exit(EXIT_SUCCESS);
}