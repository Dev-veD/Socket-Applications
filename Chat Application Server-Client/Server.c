#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void error(char *msg){
	perror(msg);
	exit(1);
}
int main(int argc, char* argv[] ){
	
	if(argc<2){
		fprintf(stderr,"Please Provide Port Number\n");
		exit(1);
	}
	
	int sockfd,newsockfd,portno,n;
	char buffer[255];
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t clilen;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0){
		error("Error In Opening The Socket");
	}

	
	bzero((char*)&serv_addr,sizeof(serv_addr));
	portno=atoi(argv[1]);
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(portno);

	if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
		error("Binding Failed");

	listen(sockfd,1);
	clilen=sizeof(cli_addr);
	
	newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
	if(newsockfd<0)
		error("Error in acccepting");
	
	while(1){
	bzero(buffer,255);
	n=read(newsockfd,buffer,255);
	if(n<0)
		error("Error in reading");
	printf("Client : %s\n",buffer);
	bzero(buffer,255);
	fflush(stdin);
	fgets(buffer,255,stdin);
	n=write(newsockfd,buffer,strlen(buffer));
	if(n<0)
		error("Error in Writing");
	int i=strcmp("bye",buffer);
	if(i==0)
		break;
	}
	close(newsockfd);
	close(sockfd);
	return 0;		
}






























