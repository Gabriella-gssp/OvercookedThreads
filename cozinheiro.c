#include "hovercooked.h"

void *cozinheiro(void *arg) {
    Cozinheiro *c = (Cozinheiro *)arg;
    c->pedidoCorreto = 1;

    while (1) {
        pthread_mutex_lock(&mutex_pedidos);
        pthread_cond_wait(&c->cond_inicio_preparo, &mutex_pedidos);

        if (pedidoAtual >= numPedidos) {
            pthread_mutex_unlock(&mutex_pedidos);
            break;
        }

        Prato *prato_info = &pratos[c->prato - 11];
        c->tempoInicioPedido = tempoTotal;
        pthread_mutex_unlock(&mutex_pedidos);

        sem_wait(&semaforo_bancada);
        c->estado = 1;
        for (int i = 0; i < MAX_BANCADAS; i++) {
            if (bancadas[i] == 0) {
                pthread_mutex_lock(&mutex_tela);
                bancadas[i] = c->id;
                c->bancada = i + 1;
                atualizar_tela();
                pthread_mutex_unlock(&mutex_tela);
                break;
            }
        }

        c->tempoRestante = prato_info->tempo_preparo_ingredientes;
        while (c->tempoRestante > 0) {
            sleep(1);
            c->tempoRestante--;
            pthread_mutex_lock(&mutex_tela);
            atualizar_tela();
            pthread_mutex_unlock(&mutex_tela);
        }

        sem_post(&semaforo_bancada);
        bancadas[c->bancada - 1] = 0;
        sem_wait(&semaforo_cozinha);
        c->estado = 2;

        for (int i = 0; i < MAX_COZINHAS; i++) {
            if (cozinhas[i] == 0) {
                cozinhas[i] = c->id;
                c->cozinha = i + 1;
                pthread_mutex_lock(&mutex_tela);
                atualizar_tela();
                pthread_mutex_unlock(&mutex_tela);
                break;
            }
        }

        c->tempoRestante = prato_info->tempo_preparo_prato;
        while (c->tempoRestante > 0) {
            sleep(1);
            c->tempoRestante--;
            pthread_mutex_lock(&mutex_tela);
            atualizar_tela();
            pthread_mutex_unlock(&mutex_tela);
        }

        sem_post(&semaforo_cozinha);
        cozinhas[c->cozinha - 1] = 0;
        c->estado = 0;
        c->prato = 0;

        pthread_mutex_lock(&mutex_tela);
        atualizar_tela();
        mvwprintw(stdscr, 20 + c->id, 0, "Cozinheiro %d preparou %s!", c->id, prato_info->nome);
        refresh();
        pthread_mutex_unlock(&mutex_tela);
        sleep(1);

        pthread_mutex_lock(&mutex_pedidos);
        pedidosConcluidos++;
        int tempoEntrega = tempoTotal - c->tempoInicioPedido;
        atualizar_pontuacao(tempoEntrega, c->pedidoCorreto);
        pthread_mutex_unlock(&mutex_pedidos);
    }

    pthread_exit(NULL);
}
