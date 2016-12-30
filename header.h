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
	int nombre; //nombre servant normalement au message LIST
} message;

int getPPID();

char *formatageNb(int nombre);
char *getStringLength(char *string);
int getTotalLength(message msg);

message initialiseMessage();

void afficheInfosStruct(message msg);

char *writeHELOmsg(message msg);
char *writeOKOKmsg(message msg);
char *writeBCSTmsgClient(message msg);
char *writeBCSTmsgServeur(message msg);
char *writeBYEEmsg(message msg);
char *writeLISTmsgClient(message msg);
char *writeLISTmsgServeur(message msg);
char *writePRVTmsgClient(message msg);
char *writePRVTmsgServeur(message msg);
char *writeSHUTmsgClient(message msg);
char *writeSHUTmsgServeur(message msg);

void deformatage(char* s, int opt);

void helo(char *s);
void heloServeur(char *s);

void okok(char *s);
void okokClient(char *s);

void bcst(char *s);
void bcstClient(char *s);

void prvt(char *s);
void prvtClient(char *s);

void byee(char *s);
void byeeClient(char *s);

void liste(char *s);
void listeClient(char *s);

void shut(char *s);
void shutClient(char *s);

char *extractId(char *s);
char *extractPseudo(char *s);
char *extractType(char *s);