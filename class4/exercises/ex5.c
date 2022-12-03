#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
    5) Implemente um programa que cria dois processos filhos. O primeiro grava em um arquivo números de 1 a 10. O segundo
    grava em um arquivo letras de A a Z. O processo pai, após cada filho terminar sua execução, lista o conteúdo dos arquivos
    criados na tela.
*/

const int ONE = 1;
const int TEN = 10;
const int A = 65;
const int Z = 90;

void cat(char *pathFile)
{
    printf("Conteúdo do arquivo: %s\n", pathFile);
    char *argv[] = {"cat", pathFile, 0};
    execvp(argv[0], argv);
}

void writeFile(char *pathFile, int startContent, int endContent)
{
    FILE *file = fopen(pathFile, "w+");
    printf("O arquivo %s está sendo sobrescrito...\n", pathFile);
    for (int i = startContent; i <= endContent; i++)
    {
        if (pathFile == "./nums.txt")
        {
            fprintf(file, "%d\n", i);
        }
        else if (pathFile == "./alphabet.txt")
        {
            fprintf(file, "%c\n", i);
        }
    }

    fclose(file);
    cat(pathFile);
}

void forkWriteFile(char *content)
{
    int status;
    pid_t child = fork();
    if (child > 0)
    {
        waitpid(child, &status, 0);
    }
    else if (content == "alphabet")
    {
        writeFile("./alphabet.txt", A, Z);
        _exit(0);
    }
    else if (content == "nums")
    {
        writeFile("./nums.txt", ONE, TEN);
        _exit(0);
    }
}

int main()
{
    forkWriteFile("nums");
    forkWriteFile("alphabet");
    return 0;
}