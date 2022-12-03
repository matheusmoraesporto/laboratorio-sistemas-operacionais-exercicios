#include <stdio.h>
#include <unistd.h>

int main()
{
    char *prog[] = {"/bin/ls"};
    char *args[] = {"/bin/ls", "-l", "/", NULL};
    char *environ[] = {NULL};

    printf("Listando o conteúdo do diretório:\n");
    execve(prog[0], args, environ); // sobrescreve a memoria do processo, o que vem abaixo daqui morre
    printf("Não deveria chegar aqui.\n");

    return 0;
}