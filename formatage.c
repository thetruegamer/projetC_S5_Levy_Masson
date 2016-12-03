#include "header.h"

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

		printf("l : %d, nombre : %d\n", longueur, nombre);
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

char *getStringLength(char *string){
	int l = strlen(string);
	char *result = formatageNb(l);
	return result;
}

//Renvoie la longueur totale des infos de la struct
int getTotalLength(message msg){
	int l = 0;
	int lId = strlen(formatageNb(msg.id));
	int lTube = strlen(formatageNb(msg.tube));
	int lLMsg = strlen(formatageNb(msg.lMsg));
	int lMsg = strlen(msg.msg);
	//longueurTotale + type + id de client + numero du tube + longueur du message + message
	l = 4 + 4 + lId + lTube + lLMsg + lMsg;
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
	msg.pseudo = "";
	msg.tube = 0;
	msg.lMsg = 0;
	msg.msg = "";

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

int main()
{
	//char *test = malloc(4*sizeof(char));
	
	// TEST FORMATAGE NOMBRE
	// test = formatageNb(690);
	// printf("test : %s\n", test);

	//TEST GET STRING LENGTH
	// test = "test";
	// test = getStringLength(test);
	// printf("test : %s\n", test);

	//TEST CREATION / INITIALISATION STRUCT
	message msg;
	msg = initialiseMessage();
	msg.longueurTotale = getTotalLength(msg);
	afficheInfosStruct(msg);

	return 0;
}