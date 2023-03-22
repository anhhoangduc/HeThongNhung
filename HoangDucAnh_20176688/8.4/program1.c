#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEYFILE_PATH  "./hello.txt"
#define ID 'S'
#define SEM_OK 0
#define SEM_NG -1

int main(void)
{
  int           semid;
  int           semval;
  key_t         keyval;
  struct sembuf buff;
  
  printf("process1      : start\n");

  keyval = ftok(KEYFILE_PATH, (int)ID);

  // Semaphore ID acquisition
  semid = semget(keyval, 1, IPC_CREAT|0660);
  printf("process1(sem-) : semID = %d\n", semid);
  // Sembuf structure setting for semaphore operation
  buff.sem_num = (ushort)0; //semaphore number
  buff.sem_op = (short)-4;  // number of resources
  buff.sem_flg = (short)0;  // wait

  //Semaphore operation
  semop(semid, &buff, 1);
  printf("process1(sem-) : sem_op = %d\n", buff.sem_op);

  // Control of semaphore (semaphore value acquisition)
  semval = semctl( semid, 0, GETVAL, 0);
  printf("process1(sem-) : semval = %d\n", semval);

  // Control of semaphore (semaphore value acquisition)
  if(semval == 0){
    // Control of semaphore (semaphore set deletion))
    if(semctl(semid, 0, IPC_RMID, 0) == SEM_NG){
      perror("process1       : semctl");
      exit(1);
    }else{
        printf("Delete semaphore set\n");
    }
  }
  printf("process1       : end\n");
  return 0;
}
