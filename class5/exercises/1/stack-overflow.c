#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char url[500] = "https://g1.globo.com";
    // char url[500];
    // printf("Informe uma url para acesso:\n");
    // scanf("%s", url);

    char keyWord[50] = "ex1";
    // char keyWord[50];
    // printf("Agora informe uma palavra chave para busca na url \"%s\"\n", url);
    // scanf("%s", keyWord);

    char *commands[][4] = {
        {"curl", "https://g1.globo.com", NULL},
        {"egrep", "-oi", "coronavirus", NULL},
        {"wc", "-l", NULL},
        {"xargs", "printf", "%d\n", NULL}};

    size_t i, n;
    int prev_pipe, pfds[2];

    n = sizeof(commands) / sizeof(*commands);
    prev_pipe = STDIN_FILENO;

    for (i = 0; i < n - 1; i++)
    {
        pipe(pfds);

        if (fork() == 0)
        {
            // Redirect previous pipe to stdin
            if (prev_pipe != STDIN_FILENO)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            // Redirect stdout to current pipe
            dup2(pfds[1], STDOUT_FILENO);
            close(pfds[1]);

            // Start command
            execvp(commands[i][0], commands[i]);

            perror("execvp failed, error on line 41");
            exit(1);
        }

        // Close read end of previous pipe (not needed in the parent)
        close(prev_pipe);

        // Close write end of current pipe (not needed in the parent)
        close(pfds[1]);

        // Save read end of current pipe to use in next iteration
        prev_pipe = pfds[0];
    }

    // Get stdin from last pipe
    if (prev_pipe != STDIN_FILENO)
    {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }

    // Start last command
    execvp(commands[i][0], commands[i]);

    exit(0);
}
