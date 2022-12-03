/*
    3) Aseguir é apresentada versão serial de um programa para cálculo de todos os números primos até um determinado valor.
    Implemente uma versão multithread para esse programa.
    Avalie o desempenho do seu programa dois valores de entrada: 10.000.000 e 100.000.000.
    Ao fazer a comparação, não imprima o resultado na tela, pois a concorrência para realização de E/S tornará o programa muito mais lento e afetará a avaliação.
    Além disso, compare essa versão, com a versão desenvolvida na Atividade 05, i.e., com multiprocessos.
*/

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *verifica_se_primo(void *args)
{
    long int numero = *((long int *)args);
    long int ant;
    for (ant = 2; ant <= (long int)sqrt(numero); ant++)
    {
        if (numero % ant == 0)
        {
            pthread_exit("0");
        }
    }
    if (ant * ant >= numero)
    {
        pthread_exit("1");
    }
}

int main()
{
    int max;
    printf("Informe um número para identificarmos quantos números menores que ele são primos:\n");
    scanf("%d", &max);

    for (int i = 0; i <= max; i++)
    {
        void *threadResult =NULL;
        pthread_t t;
        pthread_create(&t, NULL, verifica_se_primo, &i);
        pthread_join(t, &threadResult);

        int isPrimo = atoi((char*)threadResult);
        if (isPrimo == 1)
        {
            printf("%d é primo\n", i);
        }
    }
}