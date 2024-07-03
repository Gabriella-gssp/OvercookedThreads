#include "hovercooked.h"
#include <string.h>
#include <ncurses.h>

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
