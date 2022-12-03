#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

int main()
{
    int ve, vf;
    sem_t *full, *empty;

    full = sem_open("full_sem.dat", O_CREAT, 0644, 0);   // cria dois semafaros com compartilhamento de memória em /dev/shm
    empty = sem_open("empty_sem.dat", O_CREAT, 0644, 5); // https://man7.org/linux/man-pages/man3/sem_open.3.html

    sem_init(full, 1, 0); // 1 -> semafaros comaprtilhados
    sem_init(empty, 1, 5);

    if (fork() == 0)
    { // filho = consumidor --- situação inicial -- inverno no pai
        sem_getvalue(full, &ve);
        sem_getvalue(empty, &vf);

        printf("filho (C) -- livre (%d) ocupado (%d) -- INICIO\n", ve, vf);

        for (;;)
        {
            sleep(1);        // tornando os eventos mais lentos
            sem_wait(full);  // remove um item
            sem_post(empty); // libera um espaço
            sem_getvalue(full, &vf);
            sem_getvalue(empty, &ve);
            printf("filho (C) -- livre (%d) ocupado (%d) -- item consumido\n", ve, vf);
        }
    }
    else // pai = produtor - situação inicial -- inverno no filho
    {
        sem_getvalue(empty, &ve);
        sem_getvalue(full, &vf);

        printf("pai (P) -- livre (%d) ocupado (%d) -- INICIO\n", ve, vf);
        for (;;)
        {
            sleep(1);        // tornando os eventos mais lentos
            sem_wait(empty); // consome um espaço
            sem_post(full);  // adiciona um item
            sem_getvalue(empty, &ve);
            sem_getvalue(full, &vf);
            printf("pai (P) -- livre (%d) ocupado (%d) -- item produzido\n", ve, vf);
        }
    }
}