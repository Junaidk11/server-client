/*
	A Simple Client Program to understand TCP/IP. 
*/

// Header files needed on client side to request connections to the server

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(){
	
	// Create a place holder for server socket
	int serverSock = 0; // this is linux specific, on windows OS, server/client == SOCKET type

	// Create sockaddr_in structure to hold the server specific information
	struct sockaddr_in addr; 
	
	// Create a socket for the server
	// Server socket here should match the socket of the server 
	// AF_INET = Ipv4 address family 
	// SOCK_STREAM = the socket type, same as the server we're trying to connect to.
	// The third parameter is the communication protocl, 0 indicates TCP which is used by STREAMsockets
	serverSock =  socket(AF_INET, SOCK_STREAM,0);
	
	// Fill out the sockaddr_in with information regarding the server you're connecting to
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server running on same machine as client - i.e. server is your localhost
	addr.sin_family = AF_INET; // The server's address family is ipv4
	addr.sin_port = htons(5555); // The server is assigned port 5555

	// Send connection to the server which has the configuration as set above
	connect(serverSock, (struct sockaddr *)&addr, sizeof(addr));

	// The following gets executed iff the connection was accepted by the server	
	printf("Server accepted your connection.\n");

	char buffer[1024]="Hello! How you doing?";
	
	// Send data to the server
	write(serverSock, buffer, strlen(buffer));

	printf("Message: %s, sent to the server! \n",buffer);
	
	// close connection to the server
	close(serverSock);
	
	printf("Socket closed. \n");
} 
