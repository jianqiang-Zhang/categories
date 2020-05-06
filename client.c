
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include<pthread.h>
#define MAX 2000000
#define PORT 8080 
#define SA struct sockaddr 
int sockfd, connfd;
void* thr_fn(void* arg)
{
    sleep(1);
    close(sockfd);
}
void func(int sockfd)
{
    char buff[MAX];
    int n;
    pthread_t tid;
    bzero(buff, sizeof(buff));
    printf("正在传输 \n");
    int fd = open("TEST.txt", O_RDONLY);
    read(fd, buff, sizeof(buff));
    close(fd);
    //进行传输
    //通过另一个线程来进行close
    pthread_create(&tid, NULL, thr_fn, NULL);


    write(sockfd, buff, sizeof(buff));

   

}
  
int main() 
{  
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func(sockfd); 
  
    // close the socket 
    //close(sockfd); 
} 