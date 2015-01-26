#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"
#include <stdio.h>
#include <arpa/inet.h>

int connexion(int socket_serveur) {
	int socket_client;
	const char * message_bienvenue = " Bonjour , bienvenue sur mon serveur \n ";
	socket_client = accept(socket_serveur, NULL, NULL);
	if(socket_client == -1){
		perror("accept");
		return -1;
	}
	/* On peut maintenant dialoguer avec le client */
	sleep(1);
	write(socket_client, message_bienvenue, strlen(message_bienvenue));
	return socket_client;
}

int main(){
	int socket_serveur;
	socket_serveur = creer_serveur(8080);
	if(socket_serveur == -1){
		perror("probleme creation serveur\n");
		return -1;
	}
	while(1)
		connexion(socket_serveur);
	return 0;
}
