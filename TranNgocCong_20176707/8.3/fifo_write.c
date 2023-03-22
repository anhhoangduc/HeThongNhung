#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <unistd.h>

#define FIFO_FILE_PATH "./myfifo"
#define READ_FILE_PATH "./hello.txt"
#define BUFF_SIZE 256

int main()
{
  int i;
  int fifoFd;
  int readFd;
  char buf[BUFF_SIZE];
  int size;

  //Make FIFO file
  if ( mkfifo(FIFO_FILE_PATH,0666) == -1 ){
    perror("mkfifo");
    return 0;
  }
  //Open for writing only
  if ( ( fifoFd=open(FIFO_FILE_PATH,O_WRONLY) ) == -1 ){
    perror("fifofile open");
    return 0;
  }

  //Read file
  if ( ( readFd=open(READ_FILE_PATH,O_RDONLY) ) == -1 ){
    perror("readfile open");
    return 0;
  }

  //Output to FIFO file
  while ( (size=read(readFd, buf, BUFF_SIZE)) != 0 ){
    write(fifoFd, buf, size);
  }

  close(readFd);
  close(fifoFd);
  unlink(FIFO_FILE_PATH);


  return 0;
}
 
