/*

	A simple implementation of a Http server. The client is your web-browser.
	The web-browser will send a request to the http-server in the form of a header that consists
	of a url as "http://127.0.0.1:8080" http is supported on port 8080 and 127.0.0.1 is a loopback address
	indicating that the http-server is running on the localhost (i.e. the same machine as the client)

	The http-server responds to the client in the form of a header and body. The header gives information about 
	the client requested method, the request status (i.e. if the request was processed or if there was an error), 
	the type of response the server is going to send and the length of message that the server will send in the body.
	After the header, there is a blank line, followed by the response of the http-server. 


	Note: The http_server socket setup is the same tcp server socket setup, the only difference is the port number
	assigned to the server is 8080 and the response sent by server is in the form of header followed by body.  
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
	
	// 1: server and client connection place holders - linux specifix
	// Note: In Windows OS, the client and Server connection place holders are of SOCKET type.
	int server =0, client =0; 

	/* 2: A struct of type sockaddr_in is needed to store Server configuration settings such as 
	   the Address Family (Ipv4 and Ipv6) to be used and the port number to be assigned to the
	   server. The portnumber assigned will be used by clients to request connection to the
	   server. 
    */
	struct sockaddr_in serverAddr;

	// 3: Create a socket and assign it to the server place holder
	/* The first parameter is the Address Family corresponding to IPv4 and
	   the second parameter indicates that you're creating a Stream socket type, 
	   which is a reliable socket type, and the Communication protocol to be used 
	   by this socket will be TCP, which is indicated by the 0 in the third parameter 
	*/
	server = socket(AF_INET, SOCK_STREAM,0);  

	/* 4: Fill out the server socket configurations i.e. the Port number the socket will be bind to  
		and the connection interface the socket will connect to, and the Address Family assigned to the socket. 
	*/
	serverAddr.sin_addr.s_addr = INADDR_ANY;  // the server socket can listen to connections over LAN, WIFI or any other. 
	serverAddr.sin_family = AF_INET;  // Server socket is assigned IPV4 address
	
	// 5: The server can be assigned any port number in the range of [1024,6535]
	// The numbers before 1024 are being used by the system so they're not available. 
	// For http communication, we need to use port number 8080
	serverAddr.sin_port = htons(8080);  

	// 6: Bind the created socket to the server configurations that will filled out above. 
	bind(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); 

	// 7: Listen for client connection requests
	// 	The second parameter indicates the number of client connection requests you want to hold in queue
	listen(server, 0); 
	
	printf("Listening for incoming connections...\n");
	
	// 8: Create a buffer to store data sent by a client who's connection request was accepted
	char buffer[1024]={0};

	// 9: Prepare http-server response of form header + body
	// Create a message buffer
	// Note the format of message response sent by the http-serrver -> Header followed by Body
	char message[9999];
	strcpy(message, "HTTP/1.1 200 OK\nContent-length: 47\nContent-Type: text/html\n\n<html><body><h1>Http-server here!</h1></body></html>");

	// 10: The following code will only execute if a client has requested to connect with the server created above.
	// The connection made with a client is stored in a different place holder, which allows the server to listen to multiple client requests while processing the client at the head of the queue. 
	client = accept(server, (struct sockaddr*) NULL, NULL);
	
	printf("Client connection request received and accepted. \n");

	// 11: Read the clients sent information and store it in the buffer
	// From the client you expect a header that consist of METHOD(i.e. POST/GET/DELETE) and other information, printed below. 
	read(client, buffer, sizeof(buffer)-1);
	printf("Client says: %s \n",buffer);

	// 12: Clear the buffer used to store the data sent by client
	memset(buffer, 0, sizeof(buffer));

	// 13: Send the message response to the client
	int msg_len; // if the response sent successfully to the client (which is your browser), then write() api will return 0
	msg_len = write(client, message,strlen(message));

	if(msg_len==0){
		printf("Client closed connection.\n");
		close(client);
		return -1;
	}

	// close the established connection between the client and the server
	close(client); 
	printf("Client has disconnected. \n"); 

}
