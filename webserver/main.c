#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

int connexion(int socket_serveur) {
	int socket_client;
	int pid;
	char * message_recu = malloc(50);
	const char * message_bienvenue = "Bonjour , bienvenue sur mon serveur, je vais vous chanter une petite chanson : coucou c'est moi moumou la reine des moueeeeeeeeettes qui s'en va tout droit vers euralille, fait attention, fait attention, la chanson recommence... .\nAh tchou tchou pouet pouet la voila, la totomobile, ah tchou thou pouet pouet la voila, que fait-elle donc la ! Jour mémorable de sa première sortie, touloute touloute, lorsqu'elle entra dans une confiserie, dans une confiserie ! hummmmmmmmmmm !!!!!!\nQue viens-tu faire ici?\nTu veux de l'argent ? bah t'en aura pas !\nTu veux une bonne note ? Fini ce TP !!!\nlolilol!\n#hashtag\nUn mur en brique tombe et casse ca donne quoi ? un mur cassé;";
	socket_client = accept(socket_serveur, NULL, NULL);
	pid = fork();
	if(pid == -1){
		perror("pid");
	}else if(pid == 0){	
		if(socket_client == -1){
			perror("accept");
			return -1;
		}
		/* On peut maintenant dialoguer avec le client */
		sleep(1);
		write(socket_client, message_bienvenue, strlen(message_bienvenue));
		while(1){
			read(socket_client, message_recu, 50);
			write(socket_client, message_recu, 50);
			//printf("%s\n", message_recu);
		}
	} else {
		close(socket_client);
	}
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
