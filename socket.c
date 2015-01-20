#include "socket.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>


int creer_serveur (int port){
	int socket_serveur ;
	socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
	if ( socket_serveur == -1){
		perror ( " socket_serveur " );
		/* traitement de l ’ erreur */
		return -1;
	}
	int var = bind(socket_serveur, const struct sockaddr *addr, socklen_t addrlen);	
	if(var == -1){
		perror ( " bind -> var" );
		/* traitement de l ’ erreur */
		return -1;
	}
	return 0;
}

