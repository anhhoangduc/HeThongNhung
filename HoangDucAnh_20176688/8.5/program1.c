#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MUTEX "./mySharedMutex"

int main()
{
  pthread_mutex_t mutex;
  pthread_mutexattr_t pmattr;
  int fd;
  if ((fd=open(MUTEX, O_RDWR | O_CREAT | O_CLOEXEC | O_TRUNC | O_EXCL, S_IRUSR)) < 0) {
    fd = open(MUTEX, O_RDWR | O_CLOEXEC);
  }
  perror("Open fd");

  // Initialize the mutex attribute object
  pthread_mutexattr_init(&pmattr);

  // Set mutex attribute(Setting for using mutex to inter process)
  if (pthread_mutexattr_setpshared(&pmattr, PTHREAD_PROCESS_SHARED) != 0) {
    perror("pthread_mutexattr_setpshared");
    exit(1);
  }
  
  // Initialize mutex
  pthread_mutex_init(&mutex, &pmattr);

  write(fd, &mutex, sizeof(mutex));
  perror("Write shared mutex to file");
  fchmod(fd, S_IRUSR | S_IWUSR);

  pthread_mutex_t* pm = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  // Lock mutex
  if (pthread_mutex_lock(pm) != 0) {
    perror("pthread_mutex_lock");
    exit(1);
  }
  printf("mutex lock\n");

  // Output character string to Console
  char str[100] = {0};
  printf("Input 'enter': ");
  fgets(str, sizeof(str), stdin);
  // remove newline character from fgets string
  int len = strlen(str);
  if (str[len-1] == '\n') str[len-1] = '\0';
  if (strcasecmp(str, "enter") == 0){
    printf("Hello from program 1!\n");
  }

  // Unlock mutex
  if (pthread_mutex_unlock(pm) != 0) {
    perror("pthread_mutex_unlock");
    exit(1);
  }
  printf("mutex unlock\n");

  shm_unlink(MUTEX);

  return 0;
}