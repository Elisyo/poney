#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"

int main(int argc, char ** argv){

	if (argc > 1 && strcmp(argv [1] , "-advice") == 0) {
		printf ("Don’t Panic !\n");
		return 42;
	}
	
	if (argc > 1 && strcmp(argv [1] , "-server") == 0) {
		printf ("Creation serveur !\n");
		if(creer_serveur(8080) == -1){
			printf("probleme creation serveur");
			return -1;
		}
		return 42;
	}


	sleep(1);
	printf ( "Need an advice ?\n" );

	return 0;

}
