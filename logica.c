#include "hovercooked.h"

void atualizar_pontuacao(int tempoEntrega, int pedidoCorreto) {
    if (pedidoCorreto) {
        pontuacao += 10;
        pedidosEntregues++;

        tempoMedioEntrega = (tempoMedioEntrega * (pedidosEntregues - 1) + tempoEntrega) / pedidosEntregues; 

        if (tempoEntrega < 5) {
            pontuacao += 5;
        }

        if (tempoMedioEntrega <= 5) {
            satisfacaoCliente = 100;
        } else if (tempoMedioEntrega <= 10) {
            satisfacaoCliente = 80;
        } else {
            satisfacaoCliente = 60;
        }
    } else {
        pontuacao -= 5;
        pedidosErrados++;

        satisfacaoCliente -= 10;
        if (satisfacaoCliente < 0) {
            satisfacaoCliente = 0;
        }
    }

    if (satisfacaoCliente >= 90) {
        pontuacao += 10;
    }
}

void fim_de_jogo() {
    clear();
    mvprintw(LINES / 2, (COLS - strlen("Fim de Jogo! Obrigado por jogar.")) / 2, "Fim de Jogo! Obrigado por jogar.");
    mvprintw(LINES / 2 + 1, (COLS - strlen("Pressione qualquer tecla (nao numerica) para sair.")) / 2, "Pressione qualquer tecla (nao numerica) para sair.");
    refresh();
    getch();
    endwin();

    pthread_mutex_destroy(&mutex_tela);
    pthread_mutex_destroy(&mutex_pedidos);
    sem_destroy(&semaforo_bancada);
    sem_destroy(&semaforo_cozinha);

    exit(0);
}
