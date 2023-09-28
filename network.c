/**
 * @file network.c
 * @brief Implementation of network-related functions.
 *
 * This file contains the implementation of functions related to network communication
 * for the Hex game, including functions for server-client communication and IP address retrieval.
 */


#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <arpa/inet.h>
#include "network.h"
#include "Jeu.h"
#include <ifaddrs.h>
#include "IA.h"

char ADDRESS;
int PORT;
// La fonction d'envoi et du reçois des données via les sockets (User vs User)
/**
 * @brief Handle the server-side communication with a client.
 *
 * This function handles the communication with a client on the server side.
 * It receives and sends game moves until the game ends.
 *
 * @param connfd The file descriptor of the client connection.
 * @param player The player's color (BLUE or RED).
 */
void connexionServer(int connfd, char player)
{
    
	    int *i,*j;
        
        i = (int*)malloc(sizeof(int));
	j = (int*)malloc(sizeof(int));
	
	char buff[My_MAX];
        
	// infinite loop for chat
	for (;;) {
	
		bzero(buff,sizeof(buff) );
		
		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));
		(*j) = buff[0] - 'A';
		(*i) = buff[1] - '0';
		if(board[*i][*j]==EMPTY){board[*i][*j]=player; printf("well play\n\n"); displayBoard();}
		if (player==BLUE){player= RED;} else{player=BLUE;}
		if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}
		// print buffer which contains the client contents
		printf("Position = ( %d , %d ) \n", *i, *j);
		
		
		
		bzero(buff, 3);
		
		// La position i,j à envoyer
    
		printf("Saisir la position : ");
                scanf("%s",buff);
                
		if(board[*i][*j]==EMPTY){board[*i][*j]=player; printf("well play\n\n"); displayBoard();}
		if (player==BLUE){player= RED;} else{player=BLUE;}        
		if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}
	
		// and send that buffer to client
		write(connfd, buff, sizeof(buff));

		// if msg contains "Exit" then server exit and chat ended.
		if ( *i == -1 || *j == -1) {
			printf("Server Exit...\n");
			return;
		
		}
	}
}

/**
 * @brief Print the network IP addresses of the server.
 *
 * This function retrieves and prints the network IP addresses of the server.
 * It filters out local network addresses (e.g., 192.168.x.x).
 */
void printNetworkIPAddresses(){
    struct ifaddrs *ifap, *ifa;

    if (getifaddrs(&ifap) == -1) {
        perror("Erreur lors de l'obtention des adresses IP du serveur");
        return;
    }

    for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_INET) {
            struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
            char ipAddr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(addr->sin_addr), ipAddr, INET_ADDRSTRLEN);

            // Filtrer les adresses IP du réseau local (exemple : 192.168.x.x)
            if (strncmp(ipAddr, "192.168.", 8) == 0 || strncmp(ipAddr, "10.", 3) == 0 || strncmp(ipAddr, "172.", 4) == 0) {
                printf("Adresse IP du serveur : %s:%d\n", ipAddr, PORT);
            }
        }
    }

    freeifaddrs(ifap);
}

/**
 * @brief Initialize and run the server for a User vs User game.
 *
 * This function initializes and runs the server for a User vs User game.
 * It sets up the server socket, accepts client connections, and handles the game.
 */
void serverVsClient(int port)
{
	socklen_t len;
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(port);
	
	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);
	printNetworkIPAddresses();
	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// La communication entre le Joueur 1 et le Joueur 2
	connexionServer(connfd, BLUE);

	// Fermer la socket
	close(sockfd);
	
	return;
}

/**
 * @brief Handle the client-side communication with the server.
 *
 * This function handles the communication with the server on the client side.
 * It sends and receives game moves until the game ends.
 *
 * @param sockfd The socket file descriptor for the client.
 * @param player The player's color (BLUE or RED).
 */
void connexionClient(int sockfd, char player)
{
    int *i,*j;
    i = (int*) malloc (sizeof(int));
    j = (int*) malloc (sizeof(int));
    char buff[My_MAX];
    
    for (;;) {
        bzero(buff, sizeof(buff));
        
        printf("Saisir (i,j) : ");
        scanf("%d%d",i,j);  
	buff[0] = (*i) + '0';
	buff[1] = (*j) + '0';        
        if(board[*i][*j]==EMPTY){board[*i][*j]=player; printf("well play\n\n"); displayBoard();}
		if (player==BLUE){player= RED;} else{player=BLUE;}
		if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}
		write(sockfd, buff, sizeof(buff));
        
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
	(*i) = buff[0] - '0';
	(*j) = buff[1] - '0';        
        printf("La couple ( i , j ) = ( %d , %d ) \n", *i, *j);
        if(board[*i][*j]==EMPTY){board[*i][*j]=player; printf("well play\n\n"); displayBoard();}
		if (player==BLUE){player= RED;} else{player=BLUE;}
        if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}
		
		if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

/**
 * @brief Initialize and run the client for a User vs Server game.
 *
 * This function initializes and runs the client for a User vs Server game.
 * It connects to the server, communicates with it, and handles the game.
 */
void clientVsServer(int port, char address[])
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(address);
    servaddr.sin_port = htons(port);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
	== -1) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
 
    // function for chat
    connexionClient(sockfd, BLUE);
 
    // close the socket
    close(sockfd);
}

void menu(int port, char address[]){
  
  int choix;
  
  printf("\nSaisir la valeur qui correspond à votre position sur le réseau local : ");
  printf("\n\t 1- Server.");
  printf("\n\t 2- Client.\n\n");
  
  scanf("%d",&choix);
  
  if(choix==1)
    serverVsClient(port);
  else if(choix==2)
    clientVsServer(port, address);
  else
    exit(0);
  
  }

/*int main(){
  
  menu();
  
  return 0;
  
  }*/

/**
 * @brief Handle the server-side communication with an AI player.
 *
 * This function handles the communication with an AI player on the server side.
 * It receives and sends game moves until the game ends, with AI moves.
 *
 * @param connfd The file descriptor of the client connection.
 * @param player The player's color (BLUE or RED).
 */
void connexionServeria(int connfd, char player)
{
    
	    int *i,*j;
        
        i = (int*)malloc(sizeof(int));
	j = (int*)malloc(sizeof(int));
	
	char buff[My_MAX];
    int turn ;  
	// infinite loop for chat
	for (;;) {
	
		bzero(buff,sizeof(buff) );
		
		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));
		(*i) = buff[0] - '0';
		(*j) = buff[1] - '0';
		if(board[*i][*j]==EMPTY){board[*i][*j]=player; printf("well play\n\n"); displayBoard();}
		turn ++;
		if (player==BLUE){player= RED;} else{player=BLUE;}
		if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}
		// print buffer which contains the client contents
		printf("( i , j ) = ( %d , %d ) \n", *i, *j);
		
		
		
		bzero(buff, 3);
		
		// La position i,j à envoyer
    
		printf("Saisir (i,j) : ");
        Move bestMove = getBestMove(board, turn, player);
		(*j) = bestMove.row;
		(*i) = bestMove.col ;
		buff[0] = (*i) + '0';
		buff[1] = (*j) + '0';
		if(board[*i][*j]==EMPTY){board[*i][*j]=player; printf("well play\n\n"); displayBoard();}
		if (player==BLUE){player= RED;} else{player=BLUE;}        
		turn ++;
		if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}
	
		// and send that buffer to client
		write(connfd, buff, sizeof(buff));

		// if msg contains "Exit" then server exit and chat ended.
		if ( *i == -1 || *j == -1) {
			printf("Server Exit...\n");
			return;
		
		}
	}
}
void serverVsClientia(int port)
{
	socklen_t len;
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(port);
	
	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);
	printNetworkIPAddresses();
	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// La communication entre le Joueur 1 et le Joueur 2
	connexionServeria(connfd, BLUE);

	// Fermer la socket
	close(sockfd);
	
	return;
}


/**
 * @brief Handle the client-side communication with the server (AI vs AI).
 *
 * This function handles the communication with the server on the client side for an AI vs AI game.
 * It sends and receives AI moves until the game ends.
 *
 * @param sockfd The socket file descriptor for the client.
 * @param player The player's color (BLUE or RED).
 */
void connexionClientia(int sockfd, char player)
{
    int *i,*j;
    i = (int*) malloc (sizeof(int));
    j = (int*) malloc (sizeof(int));
    char buff[My_MAX];
    int turn;
    for (;;) {
        bzero(buff, sizeof(buff));
        
        printf("Saisir (i,j) : ");
        Move bestMove = getBestMove(board, turn, player);
		(*j) = bestMove.row;
		(*i) = bestMove.col ;
	buff[0] = (*i) + '0';
	buff[1] = (*j) + '0';        
        if(board[*i][*j]==EMPTY){board[*i][*j]=player; printf("well play\n\n"); displayBoard();}
		if (player==BLUE){player= RED;} else{player=BLUE;}
		turn ++;
		if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}
		write(sockfd, buff, sizeof(buff));
        
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
	(*i) = buff[0] - '0';
	(*j) = buff[1] - '0';        
        printf("La couple ( i , j ) = ( %d , %d ) \n", *i, *j);
        if(board[*i][*j]==EMPTY){board[*i][*j]=player; printf("well play\n\n"); displayBoard();}
		if (player==BLUE){player= RED;} else{player=BLUE;}
        turn ++;
		if (CheckVictory(player, board)){printf("Victory player %c, you're so strong dude !", player);break;}
		
		if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}
 
void clientVsServeria(int port, char address[])
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(address);
    servaddr.sin_port = htons(port);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
	== -1) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
 
    // function for chat
    connexionClientia(sockfd, BLUE);
 
    // close the socket
    close(sockfd);
}

void menuia(int port, char address[]){
  
  int choix;
  
  printf("\nSaisir la valeur qui correspond à votre position sur le réseau local : ");
  printf("\n\t 1- Server.");
  printf("\n\t 2- Client.\n\n");
  
  scanf("%d",&choix);
  
  if(choix==1)
    serverVsClientia(port);
  else if(choix==2)
    clientVsServeria(port, address);
  else
    exit(0);
  
  }
