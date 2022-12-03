#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
    4) Implemente um programa que crie uma cadeia de processos N processos (além do pai). A cadeia deve obedecer a seguinte
    sequência: 1o processo cria o 2o processo, 2o processo cria o 3o processo, ..., No – 1 processo cria o No processo. Cada processo
    deve imprimir seu PID e o PID do seu pai (ou PPID). Garanta que a informação exibida na tela ocorrerá na ordem inversa da
    criação dos processos, ou seja, inicialmente aparece as informações do No processo (PID e PPID), depois do No – 1, ..., depois
    do 2o e por fim do 1o.
*/

bool isBiggerTen(int x)
{
    return x > 10;
}

bool isSmallerZero(int x)
{
    return x < 0;
}

void validInput(int *n)
{
    printf("Informe a quantidade de processos filhos que serão criados:\n");
    scanf("%d", n);

    while (isBiggerTen(*n) || isSmallerZero(*n))
    {
        if (isBiggerTen(*n))
        {
            printf("A quantidade informada é maior que 10, por favor informe um valor igual ou menor que 10.\n");
        }
        else if (isSmallerZero(*n))
        {
            printf("A quantidade informada é negativa, por favor informe um valor positivo.\n");
        }
        scanf("%d", n);
    }
}

void printProcessInfo()
{
    printf("O pid do processo é:%d. O pid do processo pai é:%d.\n", getpid(), getppid());
}

void recursiveFork(int n)
{
    // ponto de parada, quando chegar a 0, significa que este é o último processo a ser criado
    if (n <= 0)
    {
        printProcessInfo();
        _exit(0);
    }

    int status;
    pid_t childPid = fork();
    if (childPid > 0) // se está no fluxo do processo pai, então apenas espera seu filho executar
    {
        waitpid(childPid, &status, 0);
        printProcessInfo();
    }
    else // se está no fluxo do filho, então precisa forkar
    {
        recursiveFork(n - 1);
    }
}

int main()
{
    int n;
    validInput(&n);
    recursiveFork(n - 1);
    return 0;
}