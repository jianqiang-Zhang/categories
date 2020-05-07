#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main()
{
   int fd=open("TESTDA.txt",O_WRONLY|O_CREAT|O_APPEND,0777);
   for(int i=0;i<100000000;i++)
   {
      write(fd,"number",sizeof("number"));
      //write(fd,i,sizeof(i));
   }
   close(fd);


}
