#include "socket.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void traitement_signal(int sig){
	int status;	
	printf("Signal%dreçu\n",sig);
	if (sig == SIGCHLD)
	{
		wait(&status);
		if (WIFSIGNALED(status))
			printf("Fils terminé par signal: %d\n", WTERMSIG(status));
	}
}

void initialiser_signaux(void){
	if(signal(SIGPIPE ,SIG_IGN) == SIG_ERR)
		perror ("signal");
	struct sigaction sa;
	sa.sa_handler = traitement_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(sigaction(SIGCHLD, &sa, NULL) == -1){
		perror("sigaction(SIGCHLD)");
	}
}

int creer_serveur (int port){
	int socket_serveur ;
	int optval = 1;
	initialiser_signaux();
	socket_serveur = socket(AF_INET ,SOCK_STREAM ,0);
	if (socket_serveur == -1){
		/* traitement de l ’ erreur */
		perror("socket_serveur");
		return -1;
	}
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET; /* Socket ipv4 */
	saddr.sin_port = htons(port); /* Port d ’ écoute */
	saddr.sin_addr.s_addr = INADDR_ANY; /* écoute sur toutes les interfaces */
	if(setsockopt(socket_serveur , SOL_SOCKET , SO_REUSEADDR , &optval , sizeof(int)) == -1){
		perror("setsockopt");
		return -1;
	}
	if (bind(socket_serveur, (struct sockaddr *)& saddr, sizeof(saddr)) == -1){
		/* traitement de l ’ erreur */		
		perror("bind socker_serveur");
		return -1;
	}
	if (listen(socket_serveur, 10) == -1){
		/* traitement d ’ erreur */
		perror("listen socket_serveur");
		return -1;
	}
	return socket_serveur;
}


