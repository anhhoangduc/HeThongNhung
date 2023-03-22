#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHIMSIZE 10
#define KEYFILE_PATH "shmfile"
#define PROJ_CHAR    65

int main()
{
  int       shmsize;
  int       shmid;
  key_t     keyval;
  int       *str;

  keyval = ftok( KEYFILE_PATH,PROJ_CHAR);
  shmsize = SHIMSIZE;

  //Get the shared memory ID
  if ((shmid = shmget(keyval,shmsize*sizeof(int),
                      IPC_CREAT|0660)) == -1){
    perror("shmget");
    exit(1);
  }
   char *head = (char *)shmat(shmid,(void*)0,0);
   
   printf("Write Data: ");
   scanf("%s",head);
  //Detach the shared memory
  if( shmdt((void*)head ) == -1){
    perror("shmdt");
    exit(1);
  }
  //Delete the shared memory
//   if( shmctl(shmid,IPC_RMID,0) == -1 ){
//     perror("shmctl");
//     exit(1);
//   }

  return 0;
}
