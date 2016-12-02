/**
 * Nom : tchatche.c
 * Auteurs : Bastien MASSON / Corentin LEVY
 * Dernière modification : 1/12/16
 * Description : Ce fichier est un client, il envoie des messages au serveur et affiche pour l'utilisateur
 */

#include "header.h"

char *formatageNb(message msg){
	if(strlen(msg.longueurTotale)) > 4){
		perror("Message trop long");
		exit(1);
	}
	printf("longeur : %d\n", strlen(msg.longueurTotale));
	return "";
}


int main(int argc, char **argv)
{
	int fd;
	char *myfifo = "/tmp/S";
	message msg;
	msg.msg = malloc(MAX_BUF*sizeof(char));

	if((fd = open(myfifo, O_WRONLY)) == -1){
		perror("open");
		exit(1);
	}

	printf("Bienvenue dans le MALE tchat !\n");
	printf("Pseudo ? >\n");
	fgets(msg.msg, MAX_BUF, stdin);
	//TO DO FORMATER LA CHAINE POUR RENVOYER LE PSEUDO
	if((write(fd, msg.msg, strlen(msg.msg)) == -1)){
		perror("write");
		exit(1);
	}

	while(1){
		printf("#> \n");
		if(strcmp((fgets(msg.msg, MAX_BUF, stdin)), "quit\n") != 0){
			if((write(fd, msg.msg, strlen(msg.msg)) == -1)){
				perror("write");
				exit(1);
			}
			exit(1);
		}
		if((write(fd, msg.msg, strlen(msg.msg)) == -1)){
			perror("write");
			exit(1);
		}
	}

	close(fd);
	unlink(myfifo);
	return 0;
}