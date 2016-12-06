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

typedef struct 
{
	char *pseudo;
	char *tube;
	int id;
} utilisateur;

int getPPID();

char *formatageNb(int nombre);
char *getStringLength(char *string);
int getTotalLength(message msg);

message initialiseMessage();
utilisateur initialiseUser(message msg);

void afficheInfosStruct(message msg);

char *writeHELOmsg(message msg);
char *writeOKOKmsg(message msg);
char *writeBCSTmsgClient(message msg);
char *writeBCSTmsgServeur(message msg);

void deformatage(char* s, int opt);

void helo(char *s);
void heloServeur(char *s);

void okok(char *s);
void okokClient(char *s);

void bcst(char *s);
void bcstClient(char *s);

char *extractId(char *s);
char *extractPseudo(char *s);
char *extractType(char *s);