# Makefile para o projeto Hovercooked

CC=gcc
CFLAGS=-Wall -Wextra -pthread
LIBS=-lncurses

SRCS=hovercooked.c tela.c gerente.c cozinheiro.c logica.c pedido.c
OBJS=$(SRCS:.c=.o)

EXEC=hovercooked

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LIBS)

hovercooked.o: hovercooked.c hovercooked.h
	$(CC) $(CFLAGS) -c hovercooked.c -o hovercooked.o

tela.o: tela.c hovercooked.h
	$(CC) $(CFLAGS) -c tela.c -o tela.o

gerente.o: gerente.c hovercooked.h
	$(CC) $(CFLAGS) -c gerente.c -o gerente.o

cozinheiro.o: cozinheiro.c hovercooked.h
	$(CC) $(CFLAGS) -c cozinheiro.c -o cozinheiro.o

logica.o: logica.c hovercooked.h
	$(CC) $(CFLAGS) -c logica.c -o logica.o

pedido.o: pedido.c hovercooked.h
	$(CC) $(CFLAGS) -c pedido.c -o pedido.o

clean:
	rm -f $(EXEC) $(OBJS)
