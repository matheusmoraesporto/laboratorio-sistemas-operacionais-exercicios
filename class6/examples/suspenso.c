#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

volatile sig_atomic_t counter = 0;

void tratador(int signum)
{
    counter++;
}

int main()
{
    sigset_t mask;
    struct sigaction action;
    memset(&action, 0, sizeof(action));

    action.sa_handler = &tratador;
    sigaction(SIGUSR1, &action, NULL);

    printf("Meu PID = %d\nEnvie SIGUSR1 para continuar, ou SIGINT para sair \n", getpid());

    // seleciona todos os sinais exceto SIGINT e SIGUSR1
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGINT);

    while (1)
    {
        // torna o programa não busy wait, mas sim suspenso, assim não utiliza processamento desnecessário

        // sem essa linha, o while não para de executar
        // somente incrementa a cada USR1 capturado
        sigsuspend(&mask); // com ela, o processo só irá contar, quando receber o sinal

        sleep(1);
        printf("Contador = #%d\n", counter);
    }

    return 0;
}