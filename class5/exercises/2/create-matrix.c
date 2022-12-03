/*
    2) Multiplique duas matrizes, sendo que cada matriz é criada por processos diferentes. O cálculo da multiplicação pode ser
    realizado  em qualquer um dos processos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "element.h"

#define SERVER_PATH "multiply_matrix"
#define MAX 9

void printMatrix(int m[3][3], int matrix)
{
    char print[256];
    for (int row = 0; row < 3; row++)
    {
        char buf[256];
        sprintf(buf, "| %d %d %d |\n", m[row][0], m[row][1], m[row][2]);
        strcat(print, buf);
    }

    printf("Matrix %d is:\n%s", matrix, print);
}

void sendMatrix(int value, int row, int col, int matrix)
{
    struct sockaddr_un remote;
    memset(&remote, 0, sizeof(struct sockaddr_un));

    int client_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SERVER_PATH);

    Element data;
    data.id = matrix;
    data.col = col;
    data.row = row;
    data.value = value;

    sendto(client_socket, &data, sizeof(struct Element *), 0, (struct sockaddr *)&remote, sizeof(remote));
}

void fillMatrix(int m[3][3], int matrix)
{
    srand(time(NULL));
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int value = rand() % MAX + 1;
            m[row][col] = value;
            sendMatrix(value, row, col, matrix);
        }
    }
}

int main()
{
    srand(time(NULL));
    int forkPid = fork();
    switch (forkPid)
    {
    case -1:
        printf("Fork error");
        exit(EXIT_FAILURE);
        break;
    case 0:
        int m1[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        memset(m1, 0, sizeof(m1));
        fillMatrix(m1, 1);
        printMatrix(m1, 1);
        break;
    default:
        int status;
        int m2[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        memset(m2, 0, sizeof(m2));
        fillMatrix(m2, 2);
        printMatrix(m2, 2);
        waitpid(forkPid, &status, 0);
        break;
    }

    exit(EXIT_SUCCESS);
}