#include "header.h"

//Convertit un nombre en chaine de 4 chars et complete par des zeros devant si besoin
char *formatageNb(int nombre){
	int longueur = 0;
	int pivot = nombre;
	char *resultat = malloc(4*sizeof(char));
	char *zero = NULL;

	while(pivot){
		pivot /= 10;
		longueur++;
	}

	zero = malloc((4-longueur)*sizeof(char));

	if(longueur == 0)
		longueur++;
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

	return zero;
}



int main(int argc, char *argv[])
{
	char *test = malloc(4*sizeof(char));
	test = formatageNb(690);
	printf("test : %s\n", test);
	return 0;
}