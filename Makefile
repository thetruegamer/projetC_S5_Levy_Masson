CC=gcc
CFLAGS=-Wall
EXEC=tchatche tchatche_serveur
LDFLAGS=-pthread

all: $(EXEC) header.h

tchatche_serveur: tchatche_serveur.o
	$(CC) -o $@ $^

tchatche: tchatche.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)$(CC) -o $@ $^