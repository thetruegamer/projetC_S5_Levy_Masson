#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

#define S "/tmp/S"
#define MAX_BUF 4096

typedef struct {
	int longueurTotale;
	char type[4];
	int id;
	char *pseudo;
	char *tube;
	int lMsg;
	char *msg;
} message;