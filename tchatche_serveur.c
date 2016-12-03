/**
 * Nom : tchatche_serveur.c
 * Auteurs : Bastien MASSON / Corentin LEVY
 * Dernière modification : 1/12/16
 * Description : Ce fichier sert de serveur au programme, il reçoit les messages des clients et les redirigent
 */

#include "header.h"

int main()
{
	int fd;
	char *buf = malloc(MAX_BUF*sizeof(char));

	if((access(S, F_OK) == -1)){
		if((mkfifo(S, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) == -1){
			perror("mkfifo");
			exit(1);
		}
	}
	
	if((fd = open(S, O_RDONLY)) == -1){
		perror("open");
		exit(1);
	}

	while(1){
		if((read(fd, buf, MAX_BUF)) == -1){
			perror("read");
			exit(1);
		}
		printf("%s", buf);
		//Après lecture d'un message, remet le buffer à 0
		memset(buf, 0, MAX_BUF);
		fflush(stdout);
	}

	close(fd);
	unlink(S);

	return 0;
}