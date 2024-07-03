CC = gcc
CFLAGS = -Wall -lncurses -pthread
OBJ = hovercooked.o tela.o logica.o cozinheiro.o gerente.o pedido.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

hovercooked: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o hovercooked
