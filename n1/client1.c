#include<time.h>

#include <netdb.h> 
#include <stdio.h> 
#include<unistd.h>
#include <stdlib.h> 
#include <string.h> 
#include<fcntl.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#define MAX (70*1024*1024)
#define PORT 8080 
#define SA struct sockaddr 
int sockfd, connfd;
pthread_t tid;
char buff[MAX];

void* thr_fn(void* arg)
{
    sleep(0.000001);
    close(sockfd);
    printf("sockfd had closed\n");
}
void func(int sockfd)
{
    //clock_t start, end;
    //char buff[MAX];
    //int n;
    bzero(buff, sizeof(buff));
    printf("正在传输 \n");
    int fd = open("TEST.txt", O_RDONLY);
    read(fd, buff, sizeof(buff));
    //printf("done\n");
    close(fd);
    //进行传输
    //通过另一个线程来进行close
    pthread_create(&tid, NULL, thr_fn, NULL);
    
    //start=clock();
    write(sockfd, buff, sizeof(buff));
    printf("done\n");
    //end=clock();
    //double duration=(double)(end-start)/CLOCKS_PER_SEC;
    //printf("用时：%f\n",duration);
    //close(sockfd);

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
  
    pthread_t ptid;
    ptid=pthread_self();
    if(pthread_equal(tid,ptid))
    {
	printf("the pthread sleeped");
	sleep(1000);
    }
    exit;
    // close the socket 
    //close(sockfd); 
} 
