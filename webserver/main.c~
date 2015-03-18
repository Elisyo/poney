#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int connexion(int socket_serveur);
char * fgets_or_exit ( char * buffer , int size , FILE * stream );


int connexion(int socket_serveur) {
	int socket_client;
	int pid;
	char * message_recu = malloc(150);
	FILE *file;
	int con  = 0;
	const char * message_bienvenue = "Bonjour , bienvenue sur mon serveur, je vais vous chanter une petite chanson : coucou c'est moi moumou la reine des moueeeeeeeeettes qui s'en va tout droit vers euralille, fait attention, fait attention, la chanson recommence... .\nAh tchou tchou pouet pouet la voila, la totomobile, ah tchou thou pouet pouet la voila, que fait-elle donc la ! Jour mémorable de sa première sortie, touloute touloute, lorsqu'elle entra dans une confiserie, dans une confiserie ! hummmmmmmmmmm !!!!!!\nQue viens-tu faire ici?\nTu veux de l'argent ? bah t'en aura pas !\nTu veux une bonne note ? Fini ce TP !!!\nlolilol!\n#hashtag\nUn mur en brique tombe et casse ca donne quoi ? un mur cassé;\n------>";
	const char * httpOk = "HTTP/1.1 200 Ok\n";
	const char * httpKo = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\nContent-Length: 17\r\n\n400 Bad request\r\n";
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
		char new[4];
		char new2[9];
		int i = 0;
		int mot = 1;
		while(1){
				//Partie pour écrire
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
			
			fgets_or_exit(message_recu , 150 , file);

			// fprintf(file,"<poney>%s------>",message_recu);
			// analyseEnTete(message_recu);
			if(con == 0){
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
			}
			if(con == 0 && mot < 4){
				new[3]='\0';
				new2[8]='\0';
				if(strcmp(new,"GET") == 0){
					printf("get OK\n");
					if(strcmp(new2,"HTTP/1.1") != 0 && strcmp(new2,"HTTP/1.0") != 0){
						if(write(socket_client, httpKo, strlen(httpKo))==-1){
							perror("write message");
							exit(1);
						}
						//printf("%s\n",message_recu);
					con++;
					
					} else {
						if(write(socket_client, httpKo, strlen(httpKo))==-1){
							perror("write message");
							exit(1);
						}
					}
				}
			}else{
				printf("%s\n", message_recu);
				if(strcmp(message_recu, "\r\n")){
					printf("ligne vide\n");
					break;
				}
			}
		}
		write(socket_client, message_bienvenue, strlen(message_bienvenue));
		write(socket_client,httpOk,strlen(httpOk));
		while(1){
			fgets_or_exit(message_recu , 150 , file);
			printf("%s\n",message_recu);
		}
	} else {
		close(socket_client);
	}
	return socket_client;
}

char * fgets_or_exit ( char * buffer , int size , FILE * stream ){
	char * tmp = fgets(buffer, size, stream);
	if( tmp == NULL){
		perror("Probfgets");
		return "";
	}else{
		return tmp;
	}
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






char * request_line(char * message_recu){
	int sortie = 0;
	int con  = 0;
	char new[4];
	char new2[9];
	char * tmp;
	int i = 0;
	int mot = 1;
	
	int nbSP =0;

	char get[4];
     char * url;
	char httpVersion[9];
	char fin[3];

	for(i=0;i<strlen(message_recu);i++){
		if(i<3){
			get[i]=message_recu[i];
		}
		if(strcmp(message_recu," ")==0){
			nbSP = nbSP +1;
		}
		get[3]="\0";
		if(i>3 && nbSP!=2){		
			url[i]=message_recu[i];
		}
		if(nbSP == 2){
		
		}
		if(strcmp(message_recu[i], "\n")){
			break;
		}
	}
	
	/*
	method SP request - target SP HTTP - version CRLF;
	GET "url" HTTP/1.0"\r\n";
	GET "url" HTTP/1.0"n";
	GET "url" HTTP/1.1"\r\n";
	GET "url" HTTP/1.1"n";
	*/
	
	while(!sortie){
		if(strcmp(message_recu[i]+message_recu[i+1],"\r\n") == 0 || strcmp(message_recu[i],"n") == 0){
			sortie = 1;
		}
		i++;
	}

	
}
/*
GET / HTTP/1.1
User-Agent: curl/7.40.0
Host: localhost:8080
Accept: *//*



Écrivez une fonction qui permet d’analyser la première ligne de la requête. D’après la RFC,
cette première ligne est de la forme :
Listing 6.1 – Première ligne de la requête
request - line = method SP request - target SP HTTP - version CRLF
—method doit être GET dans notre cas ;
—request-target correspond à l’url ;
—SP représente un seul et unique espace ;
—HTTP-version correspond dans notre cas à HTTP/1.0 ou HTTP/1.1 ;
—CRLF est la succession du caractère ’\r’ et du caractère ’\n’ ou uniquement le caractère
’n’.




On propose d’utiliser le prototype suivant pour la fonction :
1. La description du protocole est donnée au format ABNF, utilisé fréquemment dans les RFC. Ce format est
relativement simple à comprendre et est défini lui même par la RFC 5234.
22
int p arse_http_request ( const char * request_line , http_request * request );
Le premier paramêtre est la première ligne envoyée par le client. Le deuxième paramètre est un
pointeur vers une structure que nous allons décrire par la suite et qui contiendra les informations
relative à la requête. Elle sera donc modifiée par la fonction. La fonction doit retourner 0 si la
requête est invalide et 1 si le format de la requête est correct.
La structure http_request est définie ainsi :
enum http_method {
HTTP_GET ,
HTTP_UNSUPPORTED ,
};
typedef struct
{
enum http_method method ;
int major_version ;
int minor_version ;
char * url ;
} http_request ;
Vous pouvez remarquer que la structure utilise un type énuméré pour stocker un identifiant de
la méthode employé. Ainsi, pour une évolution future du serveur, il suffira de rajouter des valeurs
possibles 2 dans le type énuméré et de modifier la fonction d’analyse.
*/




















