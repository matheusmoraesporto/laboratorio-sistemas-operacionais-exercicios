/*
    1) Implemente dois processos que realizam uma tarefa, colaborativamente. Um processo deve baixar páginas na Internet,
    por exemplo usando o programa curl. O segundo processo receb essas páginas e realiza um parser para encontrar a
    quantidade de uma determinada palavra, por exemplo, usando os programas egrep e wc. O segundo programa devolve a
    quantidade de ocorrências para o primeiro processo.
    Ex: $ curl https://g1.globo.com | egrep -oi 'coronavirus' | wc -l
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void tryRedirectPipe(int previousPipe)
{
    if (previousPipe != STDIN_FILENO)
    {
        dup2(previousPipe, STDIN_FILENO);
        close(previousPipe);
    }
}

int main(void)
{
    char url[500];
    printf("Informe uma url para acesso:\n");
    scanf("%s", url);

    char keyWord[50];
    printf("Agora informe uma palavra chave para busca na url \"%s\"\n", url);
    scanf("%s", keyWord);

    char *commands[][4] = {
        {"curl", url, NULL},
        {"egrep", "-oi", keyWord, NULL},
        {"wc", "-l", NULL},
        {"xargs", "printf", "%d\n", NULL}};

    int i;
    int filePipes[2];
    int previousPipe = STDIN_FILENO;
    for (i = 0; i < 3; i++)
    {
        int pipeResult = pipe(filePipes);
        if (pipeResult != 0)
        {
            printf("Erro ao gerar o pipe!");
            exit(EXIT_FAILURE);
        }

        int forkResult = fork();
        if (forkResult < 0)
        {
            printf("Erro ao gerar o fork!");
            exit(EXIT_FAILURE);
        }
        else if (forkResult == 0)
        {
            tryRedirectPipe(previousPipe);
            dup2(filePipes[1], STDOUT_FILENO);
            close(filePipes[1]);
            execvp(commands[i][0], commands[i]);
        }

        close(previousPipe);
        close(filePipes[1]);
        previousPipe = filePipes[0];
    }

    tryRedirectPipe(previousPipe);
    execvp(commands[i][0], commands[i]);
    exit(EXIT_SUCCESS);
}
