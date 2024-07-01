// tela.c

#include "hovercooked.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

void mostrar_tela_inicial() {
    tela_inicial = newwin(LINES, COLS, 0, 0);
    box(tela_inicial, 0, 0);
    mvwprintw(tela_inicial, LINES / 2 - 3, (COLS - 26) / 2, "Simulador de Restaurante");
    mvwprintw(tela_inicial, LINES / 2 - 1, (COLS - 23) / 2, "Pressione ENTER para iniciar");
    mvwprintw(tela_inicial, LINES / 2 + 1, (COLS - 14) / 2, "ou 'q' para sair");
    wrefresh(tela_inicial);

    int tecla;
    do {
        tecla = getch();
    } while (tecla != 10 && tecla != 'q');

    delwin(tela_inicial);
    if (tecla == 'q') {
        endwin();
        exit(0);
    }
}

void ocultar_tela_inicial() {
    clear();
    refresh();
}

void inicializar_ncurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    tela_pedidos = newwin(17, 20, 0, 0);
    tela_cozinheiros = newwin(11, 40, 0, 20);
    tela_recursos = newwin(11, 50, 0, 60);

    box(tela_pedidos, 0, 0);
    box(tela_cozinheiros, 0, 0);
    box(tela_recursos, 0, 0);

    mvwprintw(tela_pedidos, 0, 1, " Pedidos ");
    mvwprintw(tela_cozinheiros, 0, 1, " Cozinheiros ");
    mvwprintw(tela_recursos, 0, 1, " Recursos ");

    refresh();
    wrefresh(tela_pedidos);
    wrefresh(tela_cozinheiros);
    wrefresh(tela_recursos);
}

void atualizar_tela() {
    wclear(tela_pedidos);
    wclear(tela_cozinheiros);
    wclear(tela_recursos);

    box(tela_pedidos, 0, 0);
    box(tela_cozinheiros, 0, 0);
    box(tela_recursos, 0, 0);

    mvwprintw(tela_pedidos, 1, 1, "Pedidos:");
    for (int i = 0; i < numPedidos; i++) {
        if (i < pedidosConcluidos) {
            mvwprintw(tela_pedidos, i + 2, 1, "%d (Concluído)", pedidos[i]);
        } else {
            mvwprintw(tela_pedidos, i + 2, 1, "%d", pedidos[i]);
        }
    }

    mvwprintw(tela_cozinheiros, 1, 1, "Cozinheiros:");
    for (int i = 0; i < MAX_COZINHEIROS; i++) {
        mvwprintw(tela_cozinheiros, i + 2, 1, "Cozinheiro %d: ", i + 1);
        switch (cozinheiros[i].estado) {
            case 0:
                mvwprintw(tela_cozinheiros, i + 2, 14, "Disponivel");
                break;
            case 1:
                mvwprintw(tela_cozinheiros, i + 2, 14, "Prep. Ingredientes");
                mvwprintw(tela_cozinheiros, i + 2, 35, "(%d)", cozinheiros[i].tempoRestante);
                break;
            case 2:
                mvwprintw(tela_cozinheiros, i + 2, 14, "Prep. Prato");
                mvwprintw(tela_cozinheiros, i + 2, 25, "(%d)", cozinheiros[i].tempoRestante);
                break;
        }
    }

    mvwprintw(tela_recursos, 1, 1, "Bancadas:");
    for (int i = 0; i < MAX_BANCADAS; i++) {
        mvwprintw(tela_recursos, i + 2, 1, "Bancada %d: %s", i + 1, bancadas[i] == 0 ? "Livre" : "Ocupada");
    }

    mvwprintw(tela_recursos, MAX_BANCADAS + 2, 1, "Cozinhas:");
    for (int i = 0; i < MAX_COZINHAS; i++) {
        mvwprintw(tela_recursos, MAX_BANCADAS + i + 3, 1, "Cozinha %d: %s", i + 1, cozinhas[i] == 0 ? "Livre" : "Ocupada");
    }

    mvwprintw(stdscr, 12, 21, "Comandos:");
    for (int i = 0; i < MAX_COZINHEIROS; i++) {
        mvwprintw(stdscr, 13 + i, 21, "Cozinheiro %d: 11 (Pizza), 12 (Hamburguer), 13 (Suco)", i + 1);
    }

    refresh();
    wrefresh(tela_pedidos);
    wrefresh(tela_cozinheiros);
    wrefresh(tela_recursos);
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
