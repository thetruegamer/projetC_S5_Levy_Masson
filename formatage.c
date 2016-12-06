#include "header.h"

int IDSCLIENTS[1024];
int INDICECREATION = 0;

int getPPID(){
	int pid = getppid();
	int longueur = 0;
	char *pidString = malloc(10*sizeof(char*));
	char *pidStringFinale = malloc(10*sizeof(char*));
	int pivot = pid;

	while(pivot){
		pivot /= 10;
		longueur++;
	}
	if(longueur > 4){
		sprintf(pidString, "%d", pid);
		strncpy(pidStringFinale, pidString, 4);
	}

	return strtol(pidStringFinale,NULL,10);
}

//Convertit un nombre en chaine de 4 chars et complete par des zeros devant si besoin
char *formatageNb(int nombre){
	int longueur = 0;
	int pivot = nombre;
	char *resultat = malloc(4*sizeof(char));
	char *zero = NULL;

	if(nombre > 0){
		while(pivot){
			pivot /= 10;
			longueur++;
		}

		zero = malloc((4-longueur)*sizeof(char));

		if(longueur == 0)
			longueur = 1;

		if(longueur > 4){
			printf("Nombre trop grand !\n");
			exit(1);
		} else if(longueur == 4){
			sprintf(zero, "%d", nombre);
		} else {
			int i;
			for(i = 0; i < 4-longueur; i++)
				strcat(zero,"0");
			sprintf(resultat, "%d", nombre);
			strcat(zero, resultat);
		}
	} else if(nombre == 0) {
		zero = "0000";
	} else {
		printf("Erreur : nombre négatif !\n");
		exit(1);
	}

	return zero;
}

//Renvoie la longueur d'une chaine formatée sur 4 octets
char *getStringLength(char *string){
	int l = strlen(string);
	char *result = formatageNb(l);
	return result;
}

//Renvoie la longueur totale des infos de la struct
int getTotalLength(message msg){
	int l = 0;
	int lId = 0;
	int lTube = 0;
	int lPseudo = 0;
	int lLpseudo = 0;

	if(msg.id != 0){
		lId = strlen(formatageNb(msg.id));
	}
	int lLMsg = 0;
	int lMsg = strlen(msg.msg);
	if(lMsg != 0)
		lLMsg = strlen(formatageNb(msg.lMsg));
	if(strcmp(msg.pseudo, "") != 0 && strcmp(msg.type, "OKOK") != 0){
		lPseudo = strlen(msg.pseudo);
		lLpseudo = 4;
	}
	//longueurTotale + type + id de client + numero du tube + longueur du message + message
	l = 4 + 4 + lId + lTube + lLMsg + lMsg + lPseudo + lLpseudo;
	msg.longueurTotale = l;

	return msg.longueurTotale;
}

//Initialise une struct vide
message initialiseMessage(){
	message msg;
	msg.longueurTotale = 0;
	msg.type = "0000";
	msg.id = 0;
	msg.pseudo = malloc(MAX_BUF*sizeof(char));
	msg.tube = 0;
	msg.lMsg = 0;
	msg.msg = malloc(MAX_BUF*sizeof(char));

	return msg;
}

utilisateur initialiseUser(message msg){
	utilisateur usr;
	usr.pseudo = msg.pseudo;
	usr.id = msg.id;
	usr.tube = formatageNb(msg.tube);

	return usr;
}

//Affiche les infos d'une struct
void afficheInfosStruct(message msg){
	printf("longueur Totale :  %d\n", msg.longueurTotale);
	printf("type :             %s\n", msg.type);
	printf("id :               %d\n", msg.id);
	printf("pseudo :           %s\n", msg.pseudo);
	printf("tube :             %d\n", msg.tube);
	printf("longueur message : %d\n", msg.lMsg);
	printf("msg :              %s\n", msg.msg);
}

// Concatène les infos de la structure pour fabriquer un HELO
char *writeHELOmsg(message msg)
{
	char *resultat = malloc(getTotalLength(msg)*sizeof(char));
	msg.type = "HELO";
	strcat(resultat, formatageNb(getTotalLength(msg)));
	strcat(resultat, msg.type);
	strcat(resultat, getStringLength(msg.pseudo));
	strcat(resultat, msg.pseudo);
	strcat(resultat, getStringLength(formatageNb(msg.tube)));
	strcat(resultat, formatageNb(msg.tube));

	return resultat;
}

char *writeOKOKmsg(message msg)
{
	char *resultat = malloc(getTotalLength(msg)*sizeof(char));
	msg.type = "OKOK";
	strcat(resultat, formatageNb(getTotalLength(msg)));
	strcat(resultat, msg.type);
	strcat(resultat, formatageNb(msg.id));

	return resultat;
}

char *writeBCSTmsgClient(message msg){
	char *resultat = malloc(getTotalLength(msg)*sizeof(char));
	msg.type = "BCST";
	strcat(resultat, formatageNb(getTotalLength(msg)));
	strcat(resultat, msg.type);
	strcat(resultat, formatageNb(msg.id));
	strcat(resultat, getStringLength(msg.msg));
	strcat(resultat, msg.msg);

	return resultat;
}

char *writeBCSTmsgServeur(message msg){
	char *resultat = malloc(getTotalLength(msg)*sizeof(char));
	msg.type = "BCST";
	strcat(resultat, formatageNb(getTotalLength(msg)));
	strcat(resultat, msg.type);
	strcat(resultat, getStringLength(msg.pseudo));
	strcat(resultat, msg.pseudo);
	strcat(resultat, getStringLength(msg.msg));
	strcat(resultat, msg.msg);

	return resultat;
}

/************************
 *	DEBUT PARTIE    *
 * 			*
 *	DEFORMATAGE     *
 *			*
 ************************/

void deformatage(char* s, int opt){
	//opt vaut 0 pour le serveur, 1 pour le client
	char *substr = extractType(s);
	
	if(strcmp(substr, "HELO") == 0)
		if(opt == 0)
			helo(s);
		else
			heloServeur(s);
	else if(strcmp(substr, "OKOK") == 0)
		if(opt == 0)
			okok(s);
		else
			okokClient(s);
	else if(strcmp(substr, "BYEE") == 0)
		;
		//TO DO
	else if(strcmp(substr, "BCST") == 0)
		if(opt == 0)
			bcst(s);
		else
			bcstClient(s);
	else if(strcmp(substr, "PRVT") == 0)
		;
		//TO DO
	else if(strcmp(substr, "LIST") == 0)
		;
		//TO DO
	else if(strcmp(substr, "SHUT") == 0)
		;
		//TO DO
	else if(strcmp(substr, "DEBG") == 0)
		;
		//TO DO?
	else if(strcmp(substr, "FILE") == 0)
		;
		//TO DO
	else if(strcmp(substr, "BADD") == 0)
		;
		//TO DO
	else {
		//Cette erreur n'est jamais sensée arriver
		printf("Erreur de type !\n");
		exit(1);
	}
}

void helo(char *s){
	int fd;
	char *messageBienvenue = malloc(MAX_BUF*sizeof(char));
	message msg;
	msg = initialiseMessage();
	char *okokString = malloc(MAX_BUF*sizeof(char));
	char *buf = malloc(MAX_BUF*sizeof(char));
	char *substr = extractId(s);
	
	msg.tube = atoi(substr);
	msg.id = atoi(substr);

	if((access(substr, F_OK) == -1)){
		if((mkfifo(substr, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) == -1){
			perror("mkfifoHELO");
			exit(1);
		}
		IDSCLIENTS[INDICECREATION] = atoi(substr);
		INDICECREATION++;
	}

	if((fd = open(substr, O_WRONLY)) == -1){
		perror("openHELO");
		exit(1);
	}

	char *debut = &s[12];
	char *fin = &s[strlen(s) - 8];
	substr = calloc(1, fin - debut + 1);
	memcpy(substr, debut, fin - debut);

	msg.pseudo = substr;
	okokString = writeOKOKmsg(msg);
	okok(okokString);
}

void heloServeur(char *s){
	char *pseudo = extractPseudo(s);
	printf("Connection request by : %s - GRANTED\n", pseudo);
}

void okok(char *s){
	int fd;
	char *substr = extractId(s);

	if((fd = open(substr, O_WRONLY)) == -1){
		perror("openHELO");
		exit(1);
	}
	
	if((write(fd, s, MAX_BUF)) == -1){
		perror("write");
		exit(1);
	}
}

void okokClient(char *s) {
	char *substr = extractId(s);
	printf("[SERVEUR] Connected. Your session ID is : %s\n", substr);
}

void bcst(char *s){
	char *id = extractId(s);
	int i = 0;
}

void bcstClient(char *s){

}

/////////////////////////////////////
//FONCTIONS POUR EXTRAIRE DES INFOS//
/////////////////////////////////////

char *extractPseudo(char *s){
	char *debut = &s[12];
	char *fin = &s[strlen(s) - 8];
	char *substr = calloc(1, fin - debut + 1);
	memcpy(substr, debut, fin - debut);

	return substr;
}

char *extractId(char *s){
	char *substr = malloc(MAX_BUF*sizeof(char));

	if((strcmp(extractType(s), "OKOK") == 0) || (strcmp(extractType(s), "HELO") == 0)){
		char *debut = &s[strlen(s) - 4];
		char *fin = &s[strlen(s)];
		substr = calloc(1, fin - debut + 1);
		memcpy(substr, debut, fin - debut);
	}
	return substr;
}

char *extractType(char *s){
	char *debut = &s[4];
	char *fin = &s[8];
	char *substr = calloc(1, fin - debut + 1);
	memcpy(substr, debut, fin - debut);

	return substr;
}
// int main()
// {
// 	//char *test = malloc(4*sizeof(char));
	
// 	// TEST FORMATAGE NOMBRE
// 	// test = formatageNb(690);
// 	// printf("test : %s\n", test);

// 	//TEST GET STRING LENGTH
// 	// test = "test";
// 	// test = getStringLength(test);
// 	// printf("test : %s\n", test);

// 	//TEST CREATION / INITIALISATION STRUCT
// 	message msg;
// 	msg = initialiseMessage();
// 	msg.pseudo = "picsouze";
// 	msg.type = "HELO";
// 	msg.longueurTotale = getTotalLength(msg);
// 	afficheInfosStruct(msg);
// 	char *helo = writeHELOmsg(msg);
// 	msg.type = "okok";
// 	char *okok = writeOKOKmsg(msg);
// 	printf("%s\n", helo);
// 	printf("%s\n", okok);
// 	deformatage(helo);

// 	return 0;
// }