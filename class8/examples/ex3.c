#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int numero_itens = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void espera_tempo_aleatorio()
{
    useconds_t tempo_espera;
    tempo_espera = random() % 5000;
    usleep(tempo_espera);
}

void *produtor()
{
    while (1)
    {
        printf("PRODUTOR -> produzindo item\n");
        espera_tempo_aleatorio();
        pthread_mutex_lock(&mutex);
        numero_itens++;
        printf("PRODUTOR -> existe %d itens!\n", numero_itens);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumidor()
{
    while (1)
    {
        while (numero_itens == 0)
        {
            /* espera até que um item seja produzido */
        }

        printf("CONSUMIDOR -> consumindo item\n");
        espera_tempo_aleatorio();
        pthread_mutex_lock(&mutex);
        numero_itens--;
        printf("CONSUMIDOR -> existe %d itens!\n", numero_itens);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t threads[2];
    srand(time(NULL));
    pthread_create(&threads[0], NULL, &produtor, NULL);
    pthread_create(&threads[1], NULL, &consumidor, NULL);
    pthread_exit(NULL);
    return 0;
}