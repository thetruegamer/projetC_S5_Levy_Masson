CC=gcc
CFLAGS=-Wall -Wextra -Werror
EXEC=tchatche tchatche_serveur
LDFLAGS=-pthread

all: $(EXEC) header.h

tchatche_serveur: tchatche_serveur.o formatage.c
	$(CC) $(LDFLAGS) -o $@ $^

tchatche: tchatche.o formatage.c
	$(CC) $(LDFLAGS) -o $@ $^

formatage: formatage.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(LDFLAGS) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC) $(CC) -o $@ $^
