#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sem_p1;
sem_t sem_p2;

void espera_tempo_aleatorio()
{
    useconds_t tempo_espera;

    tempo_espera = random() % 5000;
    usleep(tempo_espera);
}

void *processo_p1()
{
    espera_tempo_aleatorio();
    printf("P1 -> inicio\n");
    espera_tempo_aleatorio();
    printf("P1 -> FIM\n");
    sem_post(&sem_p1); // incrementa e desbloqueia sem_p1
    return NULL;
}

void *processo_p2()
{
    espera_tempo_aleatorio();
    sem_wait(&sem_p1); // espera e bloqueia sem_p1
    printf("P2 -> inicio\n");
    espera_tempo_aleatorio();
    printf("P2 -> FIM\n");
    sem_post(&sem_p2); // incrementa e desbloqueia sem_p1
    return NULL;
}

void *processo_p3()
{
    espera_tempo_aleatorio();
    sem_wait(&sem_p2); // espera e bloqueia sem_p2
    printf("P3 -> inicio\n");
    espera_tempo_aleatorio();
    printf("P3 -> FIM\n");
    return NULL;
}

void *processo_p4()
{
    espera_tempo_aleatorio();
    printf("P4 -> inicio\n");
    espera_tempo_aleatorio();
    printf("P4 -> FIM\n");
    return NULL;
}

int main(){
    pthread_t threads[4];
    srand(time(NULL));
    
    sem_init(&sem_p1, 0, 0);
    sem_init(&sem_p2, 0, 0);

    pthread_create(&threads[0], NULL, &processo_p1, NULL);
    pthread_create(&threads[1], NULL, &processo_p2, NULL);
    pthread_create(&threads[2], NULL, &processo_p3, NULL);
    pthread_create(&threads[3], NULL, &processo_p4, NULL);

    pthread_exit(NULL);
    return 0;
}