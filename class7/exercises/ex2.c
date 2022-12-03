/*
    2) Implemente um programa que crie três threads, ou seja, três funções.
    Uma função deve escrever na tela “AAAAA”, a segunda “BBBBB” e a terceira “CCCCC”.
    Execute as três threads, garantindo que seja sempre escrito na tela “AAAAABBBBBCCCCC”, nessa ordem.
    Para ter certeza que a ordem impressa é a correta, independentemente da ordem do escalonamento, inclua um comando sleep (2) na segunda função, ou seja, a que escreve “BBBBB”.
*/

#include <pthread.h>
#include <stdio.h>

#include <unistd.h>

void *writeLetter(void *arg)
{
    int id = *((int *) arg);
    char letter;
    switch (id)
    {
    case 0:
        letter = 'A';
        break;
    case 1:
        letter = 'B';
        sleep(10);
        break;
    case 2:
        letter = 'C';
        break;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%c", letter);
    }
}

int main()
{
    for (int i = 0; i < 3; i++)
    {
        pthread_t t;
        pthread_create(&t, NULL, writeLetter, &i);
        pthread_join(t, NULL);
    }
}