#include "header.h"

char *formatageNb(int nombre){
	int longueur = 0;
	while(nombre){
		nombre /= 10;
		longueur++;
	}
	if(longueur == 0)
		longueur++;
	printf("l : %d\n", longueur);
	return "";
}

int main(int argc, char *argv[])
{
	//formatageNb(1);
	return 0;
}