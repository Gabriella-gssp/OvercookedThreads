#include "hovercooked.h"

void *mural_pedidos(void *arg) {
    while (pedidosConcluidos < numPedidos) {
        int prato = (rand() % 3) + 11;

        pthread_mutex_lock(&mutex_pedidos);
        if (pedidoAtual < numPedidos) {
            pedidos[pedidoAtual++] = prato;
        }
        pthread_mutex_unlock(&mutex_pedidos);

        pthread_mutex_lock(&mutex_tela);
        atualizar_tela();
        pthread_mutex_unlock(&mutex_tela);

        sleep(rand() % 5 + 1);
    }

    pthread_exit(NULL);
}