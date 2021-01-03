/*

		A simple Server Program to understand TCP/IP communication. 
*/ 

// The header files needed Socket programming on a linux OS

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(){
	
	int server =0, client =0; // server and client connection place holders - linux specifix

	// Note: In Windows OS, the client and Server connection place holders are of SOCKET type.

	/* A struct of type sockaddr_in is needed to store Server configuration settings such as 
	   the Address Family (Ipv4 and Ipv6) to be used and the port number to be assigned to the
	   server. The portnumber assigned will be used by clients to request connection to the
	   server. 
        */
	struct sockaddr_in serverAddr;

	// Create a socket and assign it to the server place holder
	/* The first parameter is the Address Family corresponding to IPv4 and the second parameter indicates that you're creating a Stream socket type, which is a reliable socket type, and the Communication protocol to be used by this socket will be TCP, which is indicated by the 0 in the third parameter */
	server = socket(AF_INET, SOCK_STREAM,0);  

	// Fill out the server socket configurations i.e. the Port number the socket will be bind to  and the connection interface the socket will connect to, and the Address Family assigned to the socket. 
	
	serverAddr.sin_addr.s_addr = INADDR_ANY;  // the server socket can listen to connections over LAN, WIFI or any other. 
	serverAddr.sin_family = AF_INET;  // Server socket is assigned IPV4 address
	
	// The server can be assigned any port number in the range of [1024,6535]
	// The numbers before 1024 are being used by the system so they're not available. 
	serverAddr.sin_port = htons(5555);  // The server is assigned to port number 5555

	// Bind the created socket to the server configurations that will filled out above. 
	bind(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); 

	// Listen for client connection requests
	// The second parameter indicates the number of client connection requests you want to hold in queue
	listen(server, 0); 
	
	printf("Listening for incoming connections...\n");
	
	// Create a buffer to store data sent by a client who's connection request was accepted
	char buffer[1024];

	// The following code will only execute if a client has requested to connect with the server created above.
	// The connection made with a client is stored in a different place holder, which allows the server to listen to multiple client requests while processing the client at the head of the queue. 
	client = accept(server, (struct sockaddr*) NULL, NULL);
	
	printf("Client connection request received and accepted. \n");

	// Read the clients sent information and store it in the buffer 

	read(client, buffer, sizeof(buffer)-1);

	printf("Client says: %s \n",buffer);

	// Clear the buffer
	memset(buffer, 0, sizeof(buffer));

	// close the established connection between the client and the server

	close(client); 

	printf("Client has disconneected. \n"); 

}
