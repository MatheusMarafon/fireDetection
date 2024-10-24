#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define SIZE 30

void *no_sensor(void *arg);
void *gerar_incendios(void *arg);
void *central(void *arg);
void imprimir_matriz();
int eh_borda(int x, int y);

#endif