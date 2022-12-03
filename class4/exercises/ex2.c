#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
    2) Implemente um programa que permita o usuário entrar com um comando e seus parâmetros, e execute o comando. Faça uso das chamadas fork() e exec().
*/

int main()
{
    char command[10];
    printf("Informe o comando que deseja executar:\n");
    scanf("%s", command);

    char args[200];
    printf("Agora informe os argumentos do commando \"%s\"\n", command);
    scanf("%s", args);

    pid_t child_pid = fork();
    int status;

    printf("%d", child_pid);
    if (child_pid > 0)
    {
        // parent code
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
        {
            printf("O comando foi executado com sucesso!\n");
        }
        else
        {
            printf("Um erro ocorreu");
        }
    }
    else if (child_pid == 0)
    {
        // child code
        printf("Executando \"%s %s\"", command, args);
        execl(command, command, &args, NULL);
        _Exit(0);
    }
    else
    {
        printf("ERROR!!");
    }

    return 0;
}