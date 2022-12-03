#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *processo_p1()
{
    printf("P1 -> inicio\n");
    printf("P1 -> FIM\n");
    return NULL;
}

void *processo_p2()
{
    printf("P2 -> inicio\n");
    printf("P2 -> FIM\n");
    return NULL;
}

void *processo_p3()
{
    printf("P3 -> inicio\n");
    printf("P3 -> FIM\n");
    return NULL;
}

void *processo_p4()
{
    printf("P4 -> inicio\n");
    printf("P4 -> FIM\n");
    return NULL;
}

int main()
{
    pthread_t threads[4];

    pthread_create(&threads[0], NULL, &processo_p1, NULL);
    pthread_create(&threads[1], NULL, &processo_p2, NULL);
    pthread_create(&threads[2], NULL, &processo_p3, NULL);
    pthread_create(&threads[3], NULL, &processo_p4, NULL);
    
    pthread_exit(NULL);
    return 0;
}