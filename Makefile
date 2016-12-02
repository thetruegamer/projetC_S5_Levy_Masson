CC=gcc
CFLAGS=-Wall -Wextra -Werror
EXEC=tchatche tchatche_serveur formatage
LDFLAGS=-pthread

all: $(EXEC) header.h

tchatche_serveur: tchatche_serveur.o
	$(CC) -o $@ $^

tchatche: tchatche.o
	$(CC) -o $@ $^

formatage: formatage.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)$(CC) -o $@ $^
