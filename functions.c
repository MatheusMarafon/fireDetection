#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

extern char floresta[SIZE][SIZE];
extern pthread_mutex_t mutex;

void *no_sensor(void *arg)
{
    int *pos = (int *)arg;
    int pos_x = pos[0];
    int pos_y = pos[1];
    free(pos);

    while (1)
    {
        pthread_mutex_lock(&mutex);

        if (floresta[pos_x][pos_y] == '@')
        { // Fogo detectado
            if (eh_borda(pos_x, pos_y))
            {
                // Comunica com a central
                printf("Incêndio na borda detectado em [%d, %d], reportando à central.\n", pos_x, pos_y);
            }
            else
            {
                // Propaga para vizinhos
                printf("Incêndio propagando em [%d, %d].\n", pos_x, pos_y);
            }
        }

        pthread_mutex_unlock(&mutex);
        usleep(100000); // Atraso para próxima leitura
    }
    return NULL;
}

void *gerar_incendios(void *arg)
{
    while (1)
    {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        pthread_mutex_lock(&mutex);
        if (floresta[x][y] == 'T')
        {
            floresta[x][y] = '@'; // Incêndio iniciado
            printf("Incêndio gerado em [%d, %d].\n", x, y);
        }
        pthread_mutex_unlock(&mutex);

        sleep(3); // Espera 3 segundos para novo incêndio
    }
    return NULL;
}

void *central(void *arg)
{
    while (1)
    {
        // Placeholder para comunicação com sensores de borda
        // Ações de combate ao fogo ou decisões da central
    }
    return NULL;
}

int eh_borda(int x, int y)
{
    return (x == 0 || x == SIZE - 1 || y == 0 || y == SIZE - 1);
}

void imprimir_matriz()
{
    system("clear");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%c ", floresta[i][j]);
        }
        printf("\n");
    }
}
