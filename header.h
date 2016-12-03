#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

//S est le tube maitre, tous les clients envoient par ce tube, et le serveur ne fait que lire dessus
#define S "/tmp/S"
#define MAX_BUF 4096

typedef struct {
	int longueurTotale;
	char *type;
	int id;
	char *pseudo;
	int tube;
	int lMsg;
	char *msg;
} message;


char *formatageNb(int nombre);
char *getStringLength(char *string);
int getTotalLength(message msg);
message initialiseMessage();
void afficheInfosStruct(message msg);