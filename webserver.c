#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>

#define PORT 80

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc,char* argv[]){
    //Step-1 : creating a sock file descriptor
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        error("Error opening sock file descriptor");
    }

    //Step-2 : create a struct sockaddr
    struct sockaddr_in address,client_addr;
    //clear it out first
    bzero((char*) &(address),sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //Step-3 : Binding server with sockfd
    if(bind(sockfd,(struct sockaddr*) &address,sizeof(address))<0){
        error("Binding error...");
    }

    //Step-4 : Listen
    if(listen(sockfd,10)<0){
        error("Error listening...");
    }

    socklen_t len = sizeof(client_addr);

    //Step-5 : Accept Client Request using accept()
    int newSockFd = accept(sockfd,(struct sockaddr*)&client_addr,&len);

    if(newSockFd < 0) {
        error("Error accepting...");
    }

    char* server_response = "HTTP/1.1 200 OK\n Content-Type:text/html\nContent-Length:72\n\n<!DOCTYPE HTML><HTML><body><h1>Hello i am simar from C-server</h1></body></HTML>";

    // while(1){
        write(newSockFd,server_response,strlen(server_response));
        printf("Response sent to client");
        close(newSockFd);
    // }

    return 0;
}
