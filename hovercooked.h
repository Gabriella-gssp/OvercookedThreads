// hovercooked.h

#ifndef HOVERCOOKED_H
#define HOVERCOOKED_H

#include <pthread.h>
#include <semaphore.h>
#include <ncurses.h>

#define MAX_PEDIDOS 15
#define MAX_COZINHEIROS 4
#define MAX_BANCADAS 3
#define MAX_COZINHAS 4

#define TEMPO_PIZZA 5
#define TEMPO_HAMBURGUER 3
#define TEMPO_SUCO 2

typedef struct {
    int codigo;
    int tempo_preparo_ingredientes;
    int tempo_preparo_prato;
    char nome[20];
} Prato;

typedef struct {
    int id;
    int estado;
    int prato;
    int tempoRestante;
    int bancada;
    int cozinha;
    pthread_cond_t cond_inicio_preparo;
    pthread_t thread;
} Cozinheiro;

extern Prato pratos[];
extern Cozinheiro cozinheiros[MAX_COZINHEIROS];
extern int bancadas[MAX_BANCADAS];
extern int cozinhas[MAX_COZINHAS];
extern int pedidos[MAX_PEDIDOS];
extern int numPedidos;
extern int tempoJogo;
extern int tempoTotal;
extern int pedidoAtual;
extern int pedidosConcluidos;

extern sem_t semaforo_bancada, semaforo_cozinha;
extern pthread_mutex_t mutex_tela, mutex_pedidos;

extern WINDOW *tela_inicial, *tela_pedidos, *tela_cozinheiros, *tela_recursos;
extern pthread_t gerente_thread, mural_pedidos_thread;

void mostrar_tela_inicial();
void ocultar_tela_inicial();
void inicializar_ncurses();
void atualizar_tela();
void *cozinheiro(void *arg);
void *gerente(void *arg);
void *mural_pedidos(void *arg);
void fim_de_jogo();

#endif
