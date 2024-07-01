// main.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hovercooked.h"

Prato pratos[] = {
    {11, TEMPO_PIZZA, TEMPO_PIZZA, "Pizza"},
    {12, TEMPO_HAMBURGUER, TEMPO_HAMBURGUER, "Hamburguer"},
    {13, TEMPO_SUCO, TEMPO_SUCO, "Suco"}
};
Cozinheiro cozinheiros[MAX_COZINHEIROS];
int bancadas[MAX_BANCADAS] = {0};
int cozinhas[MAX_COZINHAS] = {0};
int pedidos[MAX_PEDIDOS];
int numPedidos;
int tempoJogo;
int tempoTotal = 0;
int pedidoAtual = 0;
int pedidosConcluidos = 0;

sem_t semaforo_bancada, semaforo_cozinha;
pthread_mutex_t mutex_tela, mutex_pedidos;

WINDOW *tela_inicial, *tela_pedidos, *tela_cozinheiros, *tela_recursos;
pthread_t gerente_thread, mural_pedidos_thread;

int main() {
    srand(time(NULL));

    int nivel;
    printf("Escolha o nível de dificuldade (1: Fácil, 2: Médio, 3: Difícil): ");
    scanf("%d", &nivel);

    switch (nivel) {
        case 1:
            tempoJogo = -1;
            break;
        case 2:
        case 3:
            printf("Digite o tempo de jogo (segundos): ");
            scanf("%d", &tempoJogo);
            break;
        default:
            printf("Nível inválido. Usando nível fácil.\n");
            tempoJogo = -1;
    }

    int numCozinheiros = (nivel == 3) ? 4 : MAX_COZINHEIROS;
    int numBancadas = (nivel == 3) ? 2 : MAX_BANCADAS;
    int numCozinhas = numCozinheiros;

    switch (nivel) {
        case 1:
            numPedidos = (rand() % 5) + 1;
            break;
        case 2:
            numPedidos = (rand() % 5) + 6;
            break;
        case 3:
            numPedidos = (rand() % 5) + 11;
            break;
    }

    inicializar_ncurses();
    mostrar_tela_inicial();
    ocultar_tela_inicial();
    atualizar_tela();

    pthread_mutex_init(&mutex_tela, NULL);
    pthread_mutex_init(&mutex_pedidos, NULL);
    sem_init(&semaforo_bancada, 0, numBancadas);
    sem_init(&semaforo_cozinha, 0, numCozinhas);

    for (int i = 0; i < numCozinheiros; i++) {
        cozinheiros[i].id = i + 1;
        cozinheiros[i].estado = 0;
        pthread_cond_init(&cozinheiros[i].cond_inicio_preparo, NULL);
        pthread_create(&cozinheiros[i].thread, NULL, cozinheiro, (void *)&cozinheiros[i]);
    }

    pthread_create(&gerente_thread, NULL, gerente, NULL);
    pthread_create(&mural_pedidos_thread, NULL, mural_pedidos, NULL);

    while ((tempoTotal < tempoJogo || tempoJogo == -1) && pedidosConcluidos < numPedidos) {
        tempoTotal++;
        sleep(1);

        pthread_mutex_lock(&mutex_tela);
        atualizar_tela();
        pthread_mutex_unlock(&mutex_tela);

        if (tempoTotal >= tempoJogo && tempoJogo != -1) {
            fim_de_jogo();
        }
    }

    fim_de_jogo();

    return 0;
}
