/*
    1. Instale o aplicativo figlet que recebe um texto e reescreve em uma forma estilosa no terminal. Implemente um
    programa que ao receber o sinal SIGUSR2, execute uma função que execute o aplicativo figlet. O texto deve ser
    digitado pelo usuário previamente a chamada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

char msg[500];

void printMessage()
{
    execlp("figlet", "figlet", msg, NULL);
}

int main()
{
    printf("Informe uma mensagem para ser exibida quando o sinal SIGUSR2 for disparado:\nO pid do processo é %d\n", getpid());
    scanf("%s", msg);

    sigset_t mask;
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    
    sa.sa_handler = &printMessage;

    sigaction(SIGUSR2, &sa, NULL);
    
    while (1)
    {
        sigsuspend(&mask);
    }

    return 0;
}