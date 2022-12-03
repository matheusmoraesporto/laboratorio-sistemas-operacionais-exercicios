#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid;
    int status;
    child_pid = fork();
    if (child_pid == 0)
    {
        printf("Processo filho: encerrando normalmente...\n");
        sleep(3);
        _Exit(0);
    }
    else
    {
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
            printf("Processo pai: conforme esperado, filho terminou normalmente\n");
        else
            printf("Ooops, erro inesperado...\n");
        return 0;
    }
}