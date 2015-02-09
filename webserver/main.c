#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int connexion(int socket_serveur) {
	int socket_client;
	int pid;
	char * message_recu = malloc(150);
	FILE *file;
	//const char * message_bienvenue = "Bonjour , bienvenue sur mon serveur, je vais vous chanter une petite chanson : coucou c'est moi moumou la reine des moueeeeeeeeettes qui s'en va tout droit vers euralille, fait attention, fait attention, la chanson recommence... .\nAh tchou tchou pouet pouet la voila, la totomobile, ah tchou thou pouet pouet la voila, que fait-elle donc la ! Jour mémorable de sa première sortie, touloute touloute, lorsqu'elle entra dans une confiserie, dans une confiserie ! hummmmmmmmmmm !!!!!!\nQue viens-tu faire ici?\nTu veux de l'argent ? bah t'en aura pas !\nTu veux une bonne note ? Fini ce TP !!!\nlolilol!\n#hashtag\nUn mur en brique tombe et casse ca donne quoi ? un mur cassé;\n------>";
	socket_client = accept(socket_serveur, NULL, NULL);
	if(socket_client == -1){
		perror("accept");
		return -1;
	} 
	file = fdopen(socket_client, "w+");
	pid = fork();
	if(pid == -1){
		perror("pid");
	}else if(pid == 0){
		/* On peut maintenant dialoguer avec le client */
		//write(socket_client, message_bienvenue, strlen(message_bienvenue));
		
		while(1){
			/*int taille;
			if((taille = read(socket_client, message_recu, 50))<=0){
				if (taille == -1)
					perror("read message");				
				exit(taille != -1);
			}
			if(write(socket_client, message_recu, taille)==-1){
				perror("write message");
				exit(1);
			}*/
			if(fgets(message_recu, 150, file) == NULL){
				perror("fgets");
				return -1;
			}
			//fprintf(file,"<poney>%s------>",message_recu);
			char new[4];
			char new2[9];
			int i = 0;
			int mot = 1;
			//for(i = 0; i < 14; i++){
			while(mot<5 && message_recu[i] != '\n'){
				if(i<3){
					new[i] = message_recu[i];
				}else if(i>5 && i<15){
					new2[i-6] = message_recu[i];
				}
				if(message_recu[i] == ' '){
					mot++;
				}
				i++;
			}
			if(mot < 4){
				new[3]='\0';
				new2[8]='\0';
				if(strcmp(new,"GET") == 0){
					printf("coucou\n");
					printf("%s\n",new);
					printf("%s\n",new2);
					if(strcmp(new2,"HTTP/1.1") == 0 || strcmp(new2,"HTTP/1.0") == 0){
						printf("%s\n",message_recu);
					}
				} else {
					if(write(socket_client, "HTTP/1.1 400 Bad Request\nConnection: close\nContent-Length: 17\n\n400 Bad request", 79)==-1){
						perror("write message");
						exit(1);
					}
				}
			} 
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
