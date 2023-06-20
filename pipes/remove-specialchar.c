#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
   int fd1[2];
   if (pipe(fd1) == -1)
   {
      return 1;
   }
   int fd2[2];
   if (pipe(fd2) == -1)
   {
      return 1;
   }
int id = fork();
   if (id == -1)
   {
      return 2;
   }
if(id>0){
close(fd1[0]);
close(fd2[1]);
int temp;
char buf[1000];
int fd = open ("input.txt", O_RDONLY, S_IRUSR);
ssize_t size = read(fd, buf, sizeof (buf));
//write(2, buf, size);
temp= size;
while (size > 0)
{   
size = read(fd, buf, sizeof (buf));

//write(2, buf, size);

}
temp--;
   if (write(fd1[1], &temp, sizeof(int)) < 0)
         return 3;

     
 
      if (write(fd1[1], &buf, sizeof(char) *temp) < 0)
      {
         return 4;
      }
   
      close(fd1[1]);
wait(NULL);

      if (read(fd2[0], &buf, sizeof(char) * temp) <0)
         return 6; 
close(fd2[0]);
//swrite(2, buf, temp);
int fd2 = open ("output.txt", O_WRONLY, S_IWUSR);
write(fd2, buf,temp);
}
else{

int i,j;
close(fd1[1]);
close(fd2[0]);
      char buf[1000];
      if (read(fd1[0], &j, sizeof(int)) < 0)
         return 5;

     

      if (read(fd1[0], &buf, sizeof(char) * j) <0)
         return 6; 

for(i=0;i<j;i++)
{
  if(buf[i]=='&'||buf[i]=='@'||buf[i]=='%'||buf[i]=='#'||buf[i]=='*'||buf[i]=='?'||buf[i]=='&'||buf[i]=='$'||buf[i]=='"'||buf[i]=='~')
   {
    buf[i]=' ';
    }
}
   if (write(fd2[1], &buf, sizeof(char) *j) < 0)
      {
         return 4;
      }
}
return 0;
}

