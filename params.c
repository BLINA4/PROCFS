#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME_LENGTH 768
#define MAX_LENGTH 1024

int main( void )
{
  int fd, timer;
  char string[MAX_LENGTH], filename[FILENAME_LENGTH];

  printf("Please enter timer value in seconds: ");
  scanf("%i", &timer);

  if (timer <= 0)
  {
    printf("Incorrect time value!\n");

    return -1;
  }

  printf("Please enter name of file to print to: ");
  scanf("%s", filename);

  fd = open("/proc/mydev", O_RDWR);
  
  sprintf(string, "%i %s", timer, filename);
  write(fd, string, MAX_LENGTH);
  
  return 0;
}

