#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

// SINGAL -> fica sempre escutando o sinal
// SIGNALACTION -> captura o sinal só uma vez

void tratador(int signum)
{
    switch (signum)
    {
    case SIGUSR1:
        printf("Recebido sinal SIGUSR1 (%d)\n", signum);
        break;
    case SIGCONT:
        printf("Recebido sinal SIGCONT (%d)\n", signum);
        break;
    case SIGTERM:
        printf("Recebido sinal SIGTERM (%d)\n", signum);
        break;
    case SIGINT:
        printf("Recebido sinal SIGINT (%d)\n", signum);
        break;
    case SIGTSTP:
        printf("Recebido sinal SIGTSTP (%d)\n", signum);
        break;
    case SIGQUIT:
        printf("Recebido sinal SIGUSR1 (%d)\n", signum);
        break;
    }
}

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &tratador;
    printf("Meu PID = %d\n", getpid());

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGCONT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);

    for (;;)
    {
    }
    return 0;
}