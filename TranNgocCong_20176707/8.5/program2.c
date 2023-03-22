#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MUTEX "./mySharedMutex"

int main()
{
  int fd = open(MUTEX, O_RDWR | O_CLOEXEC);
  perror("Open shared mutex file");
  pthread_mutex_t* pm;
  pm = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  // Lock mutex
  if (pthread_mutex_lock(pm) != 0) {
    perror("pthread_mutex_lock");
    exit(1);
  }
  printf("mutex lock\n");

  // Output character string to Console
  printf("Hello from program 2!\n");

  // Unlock mutex
  if (pthread_mutex_unlock(pm) != 0) {
    perror("pthread_mutex_unlock");
    exit(1);
  }
  printf("mutex unlock\n");

  shm_unlink(MUTEX);

  return 0;
}