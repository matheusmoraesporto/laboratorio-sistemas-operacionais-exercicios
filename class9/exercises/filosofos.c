#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N], i, int_rand;
float float_rand;

void mostrar(void);
void pensar(int);
void pegar_garfo(int);
void por_garfo(int);
void comer(int);
void test(int);
void *acao_filosofo(void *);

sem_t mutex;
sem_t sem_fil[N];

#define MAX 10
int refeicoes = 0;
int lenRefeicoes[N]={0,0,0,0,0}; 
int lenTentativas[N]={0,0,0,0,0}; 

int main()
{
    for (int i = 0; i < N; i++)
    {
        state[i] = 0;
    }
    mostrar();

    int res;
    pthread_t thread[N];
    void *thread_result;

    // inicia os semaforos
    res = sem_init(&mutex, 0, 1);

    if (res != 0)
    {
        perror("Erro na inicialização do semaforo!");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++)
    {
        res = sem_init(&sem_fil[i], 0, 0);
        if (res != 0)
        {
            perror("Erro na inicialização do semaforo!");
            exit(EXIT_FAILURE);
        }
    }

    // cria as threads (filosofos)
    for (int i = 0; i < N; i++)
    {
        res = pthread_create(&thread[i], NULL, acao_filosofo, &i); // o argumento que será passado para a thread é &i
        if (res != 0)
        {
            perror("Erro na inicialização da thread");
            exit(EXIT_FAILURE);
        }
    }

    // faz um join nas threads
    for (int i = 0; i < N; i++)
    {
        res = pthread_join(thread[i], &thread_result);
        if (res != 0)
        {
            perror("Erro ao fazer o join nas threads!");
            exit(EXIT_FAILURE);
        }
    }

    printf("\n");
    printf("------------------------------------------------------\n");
    printf("          Estatistica do jantar dos filosofos         \n");
    printf("------------------------------------------------------\n");

    for (i = 0; i < N; i++)
    {
        printf("Filosofo %d tentou comer %d mas só comeu %d refeicoes.\n", i, lenTentativas[i], lenRefeicoes[i]);
    }

    return (0);
}

// função que mostra o estado dos N filosofos
void mostrar()
{
    for (int i = 0; i < N; i++)
    {
        if (state[i - 1] == THINKING)
        {
            printf("O filosofo %d está pensando!\n", i);
        }
        if (state[i - 1] == HUNGRY)
        {
            printf("O filosofo %d está comendo!\n", i);
        }
        if (state[i - 1] == EATING)
        {
            printf("O filosofo %d está comendo!\n", i);
        }
    }
    printf("\n");
}

// acao do filosofo
void *acao_filosofo(void *j)
{
    int i = *(int *)j;
    while (refeicoes < MAX)
    {
        pensar(i);
        pegar_garfo(i);
        comer(i);
        por_garfo(i);
    }
}

// a thread (filosofo) espera um tempo aleatória pensando ou comendo
void pensar(int i)
{
    float_rand = 0.001 * random();
    int_rand = float_rand;
    usleep(int_rand);
}

void pegar_garfo(int i)
{
    sem_wait(&mutex);
    state[i] = HUNGRY;
    mostrar();
    test(i);
    sem_post(&mutex);
    sem_wait(&sem_fil[i]);
}

// funcao que testa se o filosofo pode comer
void test(int i)
{
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        refeicoes++;
        lenRefeicoes[i]++;
        state[i] = EATING;
        mostrar();
        sem_post(&sem_fil[i]);
    }
    else {
        lenTentativas[i]++;
    }
}

void comer(int i)
{
    
    float_rand = 0.001 * random();
    state[i] = THINKING;
    mostrar();
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void por_garfo(int i)
{
    sem_wait(&mutex);
    state[i] = THINKING;
    mostrar();
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}