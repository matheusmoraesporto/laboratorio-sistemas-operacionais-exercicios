/*
    1) Utilizando Mutex, crie uma thread_C que captura a temperatura (valores randômicos) de uma fazenda a cada segundo.
    Além disso, crie uma thread_P que recebe os valores da temperatura da thread_C e processe a temperatura média a cada 10 segundos (valor parametrizado).
    Finalmente, crie uma thread_M que recebe os valores da temperatura média da thread_P
    e informe quando esse valor médio está abaixo de um linear (valor definido) para ativar a irrigação da fazenda.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define LINEAR 23

int weathers[10];
int weatherAverage = -1;

pthread_mutex_t mutexAverage = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexIrrigate = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t irrigateCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t calcAverageCond = PTHREAD_COND_INITIALIZER;

bool isAllFilled()
{
    for (int i = 0; i < 10; i++)
    {
        if (weathers[i] < 1)
        {
            return false;
        }
    }
    return true;
}

void *getWeather()
{
    printf("Temperaturas captadas:\n");
    for (int i = 0; i < 10; i++)
    {
        weathers[i] = (random() % 50) + 1;
        sleep(1);
        printf("%d°C\n", weathers[i]);
    }

    pthread_cond_signal(&calcAverageCond);
}

void *average()
{
    pthread_mutex_lock(&mutexAverage);
    if (!isAllFilled())
    {
        pthread_cond_wait(&calcAverageCond, &mutexAverage);
    }

    int sum = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += weathers[i];
    }
    weatherAverage = sum / 10;
    printf("A temperatura média é de %d°C.\n", weatherAverage);
    pthread_mutex_unlock(&mutexAverage);
    pthread_cond_signal(&irrigateCond);
}

void *canIrrigate()
{
    pthread_mutex_lock(&mutexIrrigate);
    if (weatherAverage == -1)
    {
        pthread_cond_wait(&irrigateCond, &mutexIrrigate);
    }

    char **msg;
    if (weatherAverage >= LINEAR)
    {
        printf("Irrigação habilitada.\n");
    }
    else
    {
        printf("Irrigação desabilitada.\n");
    }
    pthread_mutex_unlock(&mutexIrrigate);
}

int main()
{
    srand(time(NULL));

    pthread_t c;
    pthread_t p;
    pthread_t m;
    pthread_create(&c, NULL, &getWeather, NULL);
    pthread_create(&p, NULL, &average, NULL);
    pthread_create(&m, NULL, &canIrrigate, NULL);
    pthread_join(m, NULL);

    pthread_exit(NULL);
    return 0;
}