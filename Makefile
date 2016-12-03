CC=gcc
CFLAGS=-Wall -Wextra -Werror
EXEC=tchatche tchatche_serveur
LDFLAGS=-pthread

all: $(EXEC) header.h

tchatche_serveur: tchatche_serveur.o formatage.c
	$(CC) -o $@ $^

tchatche: tchatche.o formatage.c
	$(CC) -o $@ $^

formatage: formatage.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)$(CC) -o $@ $^
