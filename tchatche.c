/**
 * Nom : tchatche.c
 * Auteurs : Bastien MASSON / Corentin LEVY
 * Dernière modification : 4/12/16
 * Description : Ce fichier est un client, il envoie des messages au serveur et affiche pour l'utilisateur
 */

#include "header.h"

int main()
{
	int fd;
	int pid;
	char *myfifo = S;
	message msg;
	msg = initialiseMessage();
	char *chaineFinale = malloc(MAX_BUF*sizeof(char));

	if((fd = open(myfifo, O_WRONLY)) == -1){
		perror("open");
		exit(1);
	}

	printf("Bienvenue dans le MALE tchat !\n");
	printf("Pseudo ? > ");

	//On va remplir la struct msg pour l'envoi du pseudo
	fgets(msg.pseudo, MAX_BUF, stdin);
	strtok(msg.pseudo, "\n");
	msg.type = "HELO";
	pid = getPID();
	msg.tube = pid;
	chaineFinale = writeHELOmsg(msg);
	if((write(fd, chaineFinale, strlen(chaineFinale)) == -1)){
		perror("write");
		exit(1);
	}

	while(1){
		printf("#> ");
		fgets(msg.msg, MAX_BUF, stdin);
		if(strcmp(msg.msg, "\n") != 0)
		{
			// si c'est le message quit on quitte
			if(strcmp(msg.msg, "quit\n") == 0){
				if((write(fd, msg.msg, strlen(msg.msg)) == -1)){
					perror("write");
					exit(1);
				}
				exit(1);
			}
			// on écrit dans le tube
			if((write(fd, msg.msg, strlen(msg.msg)) == -1)){
				perror("write");
				exit(1);
			}
		}
	}

	close(fd);
	unlink(myfifo);
	return 0;
}