# Makefile

CC = gcc
CFLAGS = -lncurses -pthread

all: hovercooked

hovercooked: main.o cozinheiro.o gerente.o mural_pedidos.o tela.o
	$(CC) -o hovercooked main.o cozinheiro.o gerente.o mural_pedidos.o tela.o $(CFLAGS)

main.o: main.c hovercooked.h
	$(CC) -c main.c $(CFLAGS)

cozinheiro.o: cozinheiro.c hovercooked.h
	$(CC) -c cozinheiro.c $(CFLAGS)

gerente.o: gerente.c hovercooked.h
	$(CC) -c gerente.c $(CFLAGS)

mural_pedidos.o: mural_pedidos.c hovercooked.h
	$(CC) -c mural_pedidos.c $(CFLAGS)

tela.o: tela.c hovercooked.h
	$(CC) -c tela.c $(CFLAGS)

clean:
	rm -f *.o hovercooked
