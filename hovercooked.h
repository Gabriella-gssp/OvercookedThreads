#ifndef HOVERCOOKED_H
#define HOVERCOOKED_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <ncurses.h>
#include <string.h>

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
    int tempoInicioPedido; // Tempo em que o pedido foi iniciado
    int pedidoCorreto;    // Indica se o pedido foi preparado corretamente
} Prato;

typedef struct {
    int id;
    int estado;
    int prato;
    int tempoRestante;
    int bancada;
    int cozinha;
    int tempoInicioPedido; // Tempo em que o pedido foi iniciado
    int pedidoCorreto;    // Indica se o pedido foi preparado corretamente
    pthread_cond_t cond_inicio_preparo;
    pthread_t thread;
} Cozinheiro;

// Variáveis globais
extern Prato pratos[];
extern Cozinheiro cozinheiros[];
extern int bancadas[];
extern int cozinhas[];
extern int pedidos[];
extern int numPedidos;
extern int tempoJogo;
extern int tempoTotal;
extern int pedidoAtual;
extern int pedidosConcluidos;
extern int pontuacao;
extern int pedidosEntregues;
extern int pedidosErrados;
extern int tempoMedioEntrega;
extern int satisfacaoCliente;

// Semáforos e mutexes
extern sem_t semaforo_bancada;
extern sem_t semaforo_cozinha;
extern pthread_mutex_t mutex_tela;
extern pthread_mutex_t mutex_pedidos;

// Janelas NCurses
extern WINDOW *tela_inicial, *tela_pedidos, *tela_cozinheiros, *tela_recursos;

// Posições de bancadas e cozinhas
extern int posicaoXBancada[];
extern int posicaoYBancada[];
extern int posicaoXCozinha[];
extern int posicaoYCozinha[];

// Declarações de funções
void mostrar_menu_inicial();
int obter_opcao_menu();
void mostrar_tela_inicial();
void ocultar_tela_inicial();
void inicializar_ncurses();
void atualizar_tela();
void atualizar_pontuacao(int tempoEntrega, int pedidoCorreto);
void fim_de_jogo();

// Funções de threads
void *cozinheiro(void *arg);
void *gerente(void *arg);
void *mural_pedidos(void *arg);

#endif // HOVERCOOKED_H
