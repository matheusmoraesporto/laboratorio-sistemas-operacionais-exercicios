#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    if (fork() > 0)
        printf("Sou o processo pai. Meu ID: %d\n", getpid());
    else {
        // sleep(1);
        printf("Sou o processo filho. Meu ID: %d -- ID do meu pai: %d\n", getpid(), getppid());
        // se entrar nesse "else", pode ficar sem o terminal, isso significa que o processo pai encerrou e o processo filho que está executando ainda, perdeu a referencia do pai, que agora é o init
    }
    return 0;
}