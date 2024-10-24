#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

#define SIZE 30

char floresta[SIZE][SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
    pthread_t sensores[SIZE][SIZE];
    pthread_t thread_gerador, thread_central;

    // Inicializa matriz
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            floresta[i][j] = 'T'; // Define célula com sensor
        }
    }

    // Cria threads para sensores
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int *pos = malloc(2 * sizeof(int)); // Aloca memória para posição
            pos[0] = i;
            pos[1] = j;
            pthread_create(&sensores[i][j], NULL, no_sensor, pos);
        }
    }

    // Cria thread geradora de incêndios
    pthread_create(&thread_gerador, NULL, gerar_incendios, NULL);

    // Cria thread da central
    pthread_create(&thread_central, NULL, central, NULL);

    // Loop para imprimir a matriz e mostrar o estado da floresta
    while (1)
    {
        imprimir_matriz();
        sleep(1); // Atualiza a cada 1 segundo
    }

    // Aguardando finalização (opcional)
    pthread_join(thread_gerador, NULL);
    pthread_join(thread_central, NULL);

    return 0;
}
