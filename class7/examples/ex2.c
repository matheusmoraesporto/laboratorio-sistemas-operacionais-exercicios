#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char buffer;

void *produtor()
{
    char item;
    while (1)
    {
        item = 'A';
        printf("Produzi A\n");
        buffer = item;
        sleep(1);
    }
    pthread_exit(0); // status de saída
}

void *consumidor()
{
    char item;
    while (1)
    {
        item = buffer;
        printf(">>>>>>>>>>> Consumi o item %c\n", item);
        sleep(1);
    }
    pthread_exit(0); // status de saída
}

int main()
{
    pthread_t t1, t2; // declara as threads

    // cria threads: id, atributo associado na inicialização, função param função
    (void)pthread_create(&t1, NULL, produtor, NULL);
    (void)pthread_create(&t2, NULL, consumidor, NULL);

    // espera  fim das threads: id, status de saída
    (void)pthread_join(t1, NULL);
    (void)pthread_join(t2, NULL);

    return 0;
}