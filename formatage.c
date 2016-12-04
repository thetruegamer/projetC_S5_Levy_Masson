#include "header.h"

int getPID(){
	int pid = getpid();
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
			for(int i = 0; i < 4-longueur; i++)
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
	if(msg.id != 0){
		lId = strlen(formatageNb(msg.id));
	}
	int lTube = strlen(formatageNb(msg.tube));
	int lLMsg = strlen(formatageNb(msg.lMsg));
	int lMsg = strlen(msg.msg);
	int lPseudo = 0;
	int lLpseudo = 0;
	if(strcmp(msg.pseudo, "") != 0){
		lPseudo = strlen(msg.pseudo);
		lLpseudo = 4;
	}
	//longueurTotale + type + id de client + numero du tube + longueur du message + message
	l = 4 + 4 + lId + lTube + lLMsg + lMsg + lPseudo + lLpseudo;
	//Faire attention pour le pseudo ???
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
char *writeHELOmsg(message msg){
	char *resultat = malloc(getTotalLength(msg)*sizeof(char));

	strcat(resultat, formatageNb(getTotalLength(msg)));
	strcat(resultat, msg.type);
	strcat(resultat, getStringLength(msg.pseudo));
	strcat(resultat, msg.pseudo);
	strcat(resultat, getStringLength(formatageNb(msg.tube)));
	strcat(resultat, formatageNb(msg.tube));

	return resultat;
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
// 	msg.longueurTotale = getTotalLength(msg);
// 	afficheInfosStruct(msg);
// 	char *helo = writeHELOmsg(msg);
// 	printf("%s\n", helo);

// 	return 0;
// }