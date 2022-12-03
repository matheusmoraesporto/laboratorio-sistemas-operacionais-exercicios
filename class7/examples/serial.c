/*  Serial
    gcc serial.c -o serial -lm
    time ./serial
*/

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define CALLS 10

void CPU_bound(int id)
{
    int i;
    double result = 0.0;

    // Consumo de CPU
    for (i = 0; i < 10000; i++)
        result = result + sin(i) * tan(i) * sqrt(result);

    printf("%d: CPU intensiva terminada\n", id);
}

void IO_bound(int id)
{
    // Simula operações de I/O, as quais levam a bloqueio
    sleep(1);
    printf("%d: E/S intensiva termminada\n", id);
}

int main()
{
    int i;
    for (i = 0; i < CALLS; i++)
    {
        if (i % 2)
        {
            CPU_bound(i);
        }
        else
        {
            IO_bound(i);
        }
    }
    printf("\n*** Tarefas concluídas ***\n");
    return 0;
}