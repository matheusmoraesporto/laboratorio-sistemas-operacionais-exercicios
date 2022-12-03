#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
    3) Implemente um programa que crie N processos, todos filhos do mesmo pai. N é um valor fornecido pelo usuário. Todos os processos devem imprimir seu PID e PPID.
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

int main()
{
    int n;
    validInput(&n);

    printf("O processo main é o %d\n", getpid());
    printf("%d processos serão criados:\n", n);
    int status;
    for (int i = 0; i < n; i++)
    {
        pid_t child = fork();
        if (child > 0)
        {
            waitpid(child, &status, 0);
        }
        else
        {
            printf("O processo %d foi criado e o processo pai é o %d.\n", getpid(), getppid());
            _exit(0);
        }
    }

    return 0;
}
