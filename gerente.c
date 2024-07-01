// gerente.c

#include "hovercooked.h"
#include <stdio.h>
#include <unistd.h>

void *gerente(void *arg) {
    int tecla1, tecla2;

    while (tempoTotal < tempoJogo || tempoJogo == -1) {
        tecla1 = getch();
        tecla2 = getch();

        int cozinheiro = tecla1 - '0';
        int prato = (tecla2 - '0') + 10;

        if (cozinheiro >= 1 && cozinheiro <= MAX_COZINHEIROS && prato >= 11 && prato <= 13) {
            pthread_mutex_lock(&mutex_pedidos);
            if (cozinheiros[cozinheiro - 1].estado == 0) {
                cozinheiros[cozinheiro - 1].prato = prato;
                pthread_cond_signal(&cozinheiros[cozinheiro - 1].cond_inicio_preparo);
            } else {
                pthread_mutex_lock(&mutex_tela);
                mvwprintw(stdscr, 7, 0, "Cozinheiro %d ou recursos indisponíveis!", cozinheiro);
                refresh();
                pthread_mutex_unlock(&mutex_tela);
                sleep(1);
            }
            pthread_mutex_unlock(&mutex_pedidos);
        } else {
            pthread_mutex_lock(&mutex_tela);
            mvwprintw(stdscr, 7, 0, "Comando inválido!");
            refresh();
            pthread_mutex_unlock(&mutex_tela);
            sleep(1);
        }

        pthread_mutex_lock(&mutex_tela);
        atualizar_tela();
        pthread_mutex_unlock(&mutex_tela);
    }

    pthread_exit(NULL);
}
