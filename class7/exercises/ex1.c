/*
    1) Implemente um programa que crie uma cadeia de N threads(além da thread principal).
    A cadeia deve obedecer a seguinte sequência: 1a thread cria o 2a thread, 2a thread cria o 3a thread, ..., (N-1) a thread cria a Na thread.
    Cada thread deve imprimir seu ID e o ID da thread que a criou.
    Garanta que a informação exibida na tela ocorrerá na ordem inversa da criação das threads,
    ou seja, inicialmente aparecem as informações da Na thread, depois da (N-1)a, ..., depois da 2a e por fim da 1a.
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void createThread(long parent_t);
void *tFunc(void *arg);

int n;
int main()
{
    do
    {
        printf("Informe a quantidade de threads que você deseja criar:\n");
        scanf("%d", &n);

        if (n < 1)
        {
            printf("A quantidade de threads não pode ser negativa nem igual a zero.\n");
        }
        else if (n > 10)
        {
            printf("A quantidade de threads não pode ser maior que 10.\n");
        }
    } while (n < 1 || n > 10);

    createThread(getpid());
    exit(EXIT_SUCCESS);
}

void createThread(long parent_t)
{
    if (n <= 0)
    {
        pthread_exit(EXIT_SUCCESS);
    }

    pthread_t t;
    n--;
    pthread_create(&t, NULL, tFunc, (long*)t);
    pthread_join(t, NULL);

    printf("Meu ID=%ld ID da thread pai=%ld\n", t, parent_t);
    pthread_exit(EXIT_SUCCESS);
}

void *tFunc(void *arg)
{
    createThread((long)arg);
}