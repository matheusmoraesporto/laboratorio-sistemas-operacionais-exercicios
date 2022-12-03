#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/*
    1) Com base no fragmento de código apresentado no livro de Sistemas Operacionais do Tanenbaum, apresentado abaixo,
    escreva um pequeno shell (terminal ou linha de comandos) para a execução de ações simples como listar um diretório e
    verificar a hora do sistema.

    #define TRUE 1
    while(TRUE) {                           // repeat forever
        type_prompt();                      // display prompt on the screen
        read_command(command, parameter);   // read input from terminal

        if (fork != 0) {                    // fork of child process
            // Parent code
            waitpid(-1, &status, 0);        // wait fr child to exit
        } else {
            // child code
            execve(command, parameters, 0); // execute command
        }
    }
*/

#define TRUE 1

int main()
{
    while (TRUE)
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
    }

    return 0;
}