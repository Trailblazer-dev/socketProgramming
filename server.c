/*A simple server in the internet domain using TCP 
The port number is passed as an argument 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>   //contains definitions of data types use in system calls
#include<sys/socket.h>  //contains definitions of structues needed for sockets
#include<netinet/in.h>  //contains constants and structures needed for internet domain address

void error(const char *msg){
	perror(msg);
	exit(1);
}

void main(int  argc, char *argv[]){
	int sockfd,portno,n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	if(argc<3){
		fprintf(stderr,"usage %s hostname port\n",argv[0]);
		exit(0);
	}
	portno=atoi(argv[2];
	sockfd=socket(AF_INET,  SOCKET_STREAM, 0);
	if(sockefd<0){
		error("ERROR opening socket");
	}
	server=gethostbyname(argv[1]);
	if(server==NULL){
		fprintf(stderr,"ERROR,  no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr,sizeof(servaddr));
	serv_addr.sin_family =AF_INET;
	bcopy((char *)server->h_addr,
			(char *) &serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port =htons(portno);
	if( connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr))<-){
		error("ERROR connecting");
	}
	printf("Client: ");
	while(1){
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n=write(sockdfd,buffer,strlen(buffer));
	if(n<0){
		error("Error writing to socket");
	}
	bzero(buffer,256);
	n=read(sockfd,buffer,255);
	if(n<0){
		error("ERROR  reading from socket");
	}
	printf("Server: %s\n",buffer);
	int i=strncmp("Bye",buffer,3);
	if(i==0){
		break;
	}
	}

	return 0;
}
