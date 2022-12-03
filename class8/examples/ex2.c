#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_THREADS 10

int incrementa = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void espera_tempo_aleatorio()
{
    useconds_t tempo_espera;
    tempo_espera = random() % 5000;
    usleep(tempo_espera);
}

void *soma()
{
    int aux;
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);
        incrementa = incrementa + 1;
        espera_tempo_aleatorio();
        incrementa = incrementa + 1;
        aux = incrementa;
        pthread_mutex_unlock(&mutex);
        printf("%d ", aux);
    }

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, &soma, NULL);
    }
    pthread_exit(0);
    return 0;
}