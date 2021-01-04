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
