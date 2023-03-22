#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <unistd.h>
#define FIFO_FILE_PATH "./myfifo"
int main()
{
	int fifoFd;
    int size;

	char str[80];
	
    // Open in read only 
    if ( ( fifoFd=open(FIFO_FILE_PATH,O_RDONLY) ) == -1 ){
        perror("fifofile open");
        return 0;
    }

    // Print the read string and close
    while ( (size=read(fifoFd, str, 80)) != 0 ){
            printf("%s", str);
            printf("\n");
    }
    
    close(fifoFd);
	
	return 0;
}
