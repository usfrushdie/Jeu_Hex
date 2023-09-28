/**
 * @file network.h
 * @brief Header file containing functions related to network communication.
 *
 * This header file defines functions for setting up network connections,
 * creating servers and clients, and handling network communication.
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

#define My_MAX 80
extern int PORT;
#define SA struct sockaddr
extern char ADDRESS;
/**
 * @brief Establishes a connection with a client.
 *
 * This function is responsible for handling the communication with a client
 * after a connection has been established.
 *
 * @param connfd The file descriptor of the connected client.
 */
void connexionServer(int connfd, char player);

/**
 * @brief Starts a server that can accept client connections.
 *
 * This function sets up a server that listens for incoming client connections.
 * It enters a loop and accepts incoming client connections, delegating the
 * communication to the `connexionServer` function.
 */
void serverVsClient(int port);

/**
 * @brief Establishes a connection with a server.
 *
 * This function is responsible for connecting to a server as a client and
 * handling the communication with the server.
 *
 * @param sockfd The socket file descriptor used for communication with the server.
 */
void connexionClient(int sockfd, char player);

/**
 * @brief Starts a client that can connect to a server.
 *
 * This function sets up a client that can connect to a server. It initiates the
 * connection and enters a loop to handle the communication with the server,
 * delegating the communication to the `connexionClient` function.
 */
void clientVsServer(int port, char address[]);
void clientVsServeria(int port, char address[]);
/**
 * @brief Displays a menu for network communication options.
 *
 * This function displays a menu of options for network communication, allowing
 * the user to choose between starting a server or connecting as a client.
 */
void menu(int port, char address[]);

void menuia(int port, char address[]);
