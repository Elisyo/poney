#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/*On gère ici la partie serveur*/
int creer_serveur (int port){
	int socket_serveur;
	int optval = 1;
	
	/*Création de la socket serveur*/
	socket_serveur = socket(AF_INET ,SOCK_STREAM ,0);
	if (socket_serveur == -1){
		perror("socket_serveur");
		return -1;
	}

	/*Structure pour la configuration de la socket*/
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET; /* Socket ipv4 */
	saddr.sin_port = htons(port); /* Port d ’ écoute */
	saddr.sin_addr.s_addr = INADDR_ANY; /* écoute sur toutes les interfaces */
	
	/*Permet à un processus de faire un bind sur une même adresse*/
	if(setsockopt(socket_serveur , SOL_SOCKET , SO_REUSEADDR , &optval , sizeof(int)) == -1){
		perror("setsockopt");
		return -1;
	}	

	/*Configuration de la socket*/
	if (bind(socket_serveur, (struct sockaddr *)& saddr, sizeof(saddr)) == -1){	
		perror("bind socker_serveur");
		return -1;
	}

	/*Démarrage de l'attente d'un client*/
	if (listen(socket_serveur, 10) == -1){
		perror("listen socket_serveur");
		return -1;
	}

	return socket_serveur;
}
