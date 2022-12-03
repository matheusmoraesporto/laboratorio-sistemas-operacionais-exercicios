#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int data_processed;
    int file_pipes[2]; // file_pipes[0] é para ler. file_pipes[1] é para escrever.
    const char some_data[] = "123";
    pid_t fork_result;

    if (pipe(file_pipes) == 0)
    {
        fork_result = fork();
        if (fork_result == (pid_t)-1)
        {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if (fork_result == (pid_t)0)
        {
            close(0);
            dup(file_pipes[0]);
            // fechar fd[0] e fd[1] pq teremos um exec pela frente
            close(file_pipes[0]);
            close(file_pipes[1]);
            // lê os bytes e converte para hexa
            execlp("od", "od", "-c", (char*)0);
            exit(EXIT_FAILURE);
        }
        else {
            close(file_pipes[0]);
            data_processed = write(file_pipes[1], some_data, strlen(some_data));
            printf("%d - wrote %d bytes \n", (int)getpid(), data_processed);
            close(file_pipes[1]);
        }
    }

    exit(EXIT_SUCCESS);
}