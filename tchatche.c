/**
 * Nom : tchatche.c
 * Auteurs : Bastien MASSON / Corentin LEVY
 * Dernière modification : 4/12/16
 * Description : Ce fichier est un client, il envoie des messages au serveur et affiche pour l'utilisateur
 */

#include "header.h"

extern int IDSCLIENTS[];
extern char *PSEUDOS[];
extern int INDICECREATION;

void *thread1(){
	int fdClient;
	char *fifoClient = malloc(MAX_BUF*sizeof(char));
	char *buf = malloc(MAX_BUF*sizeof(char));
	int pid = getPPID();

	fifoClient = formatageNb(pid);
	//printf("fifoClient : %s\n", fifoClient);
	mkfifo(fifoClient, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	
	if((fdClient = open(fifoClient, O_RDONLY)) == -1){
		perror("open");
		exit(1);
	}

	while(1){
		if((read(fdClient, buf, MAX_BUF)) == -1){
			perror("read");
			exit(1);
		}
		if(strcmp(buf, "") != 0)
			deformatage(buf, 1);
			//affiche les chaines formatées qui viennent du serveur, utile pour débug
			//printf("%s\n", buf);
		memset(buf, 0, MAX_BUF);
		fflush(stdout);
	}

	close(fdClient);
	unlink(fifoClient);
	pthread_exit(NULL);
}

int main()
{
	pthread_t t1;
	int fd;
	int pid;
	char *myfifo = S;
	char *chaineFinale = malloc(MAX_BUF*sizeof(char));
	message msg;
	msg = initialiseMessage();

	if((fd = open(myfifo, O_WRONLY)) == -1)
	{
		perror("open");
		exit(1);
	}

	printf("Welcome to the MALE chat!\n");
	printf("Enter your name for this session > ");

	//On va remplir la struct msg pour l'envoi du pseudo
	fgets(msg.pseudo, MAX_BUF, stdin);
	strtok(msg.pseudo, "\n");

	pid = getPPID();
	msg.type = "HELO";
	msg.tube = pid;
	msg.id = pid;

	//On rédige un message de type HELO
	chaineFinale = writeHELOmsg(msg);
	if((write(fd, chaineFinale, strlen(chaineFinale)) == -1))
	{
		perror("write");
		exit(1);
	}

	if(pthread_create(&t1, NULL, thread1, NULL) == -1) {
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	while(1){
		
		fgets(msg.msg, MAX_BUF, stdin);
		if(strcmp(msg.msg, "\n") != 0)
		{
			// si c'est le message quit on quitte
			if(strcmp(msg.msg, "/quit\n") == 0){
				chaineFinale = writeBYEEmsg(msg);
				if((write(fd, chaineFinale, strlen(chaineFinale)) == -1)){
					perror("write");
					exit(1);
				}
				sleep(0.5);
				break;
			} else if(strcmp(msg.msg, "/list\n") == 0) {
				chaineFinale = writeLISTmsgClient(msg);
				msg.tube = pid;
				msg.id = pid;
				if((write(fd, chaineFinale, strlen(chaineFinale)) == -1)){
					perror("write");
					exit(1);
				}
			} else {
				msg.tube = pid;
				msg.id = pid;
				char *bcst = malloc(1024*sizeof(char));
				strcpy(bcst, msg.msg);
				char *prive = strtok(bcst, " ");
				if(strcmp(prive, "/p") == 0){
					msg.pseudo = strtok(NULL, " ");
					msg.msg = strtok(NULL, "\n");
					strtok(msg.msg, "\n");

					chaineFinale = writePRVTmsgClient(msg);
					// on écrit dans le tube
					if((write(fd, chaineFinale, strlen(chaineFinale)) == -1)){
						perror("write");
						exit(1);
					}
				} else {
					strtok(msg.msg, "\n");
					chaineFinale = writeBCSTmsgClient(msg);
					// on écrit dans le tube
					if((write(fd, chaineFinale, strlen(chaineFinale)) == -1)){
						perror("write");
						exit(1);
					}
				}
			}
		}
	}

	pthread_cancel(t1);
	
	return 0;
}