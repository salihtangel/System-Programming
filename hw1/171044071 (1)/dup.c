#include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <unistd.h>
	#include <string.h>

  #if 0
  int fw=open("chinaisbetter.txt", O_APPEND|O_WRONLY);
  dup2(fw,1);
  printf("Are you kidding me? \n");
  #endif
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  int fd1 = open("file.txt", O_RDWR);
  int fd2 = open("file2.txt", O_WRONLY | O_CREAT, 0644);

  // Duplicate fd1 and replace fd2 with the duplicate
  dup2(fd1, fd2);

  // Now write to fd2 (which is a duplicate of fd1)
  char buffer[1024];
  ssize_t bytes_read;

  #if 0
  while ((bytes_read = read(fd2, buffer, sizeof(buffer))) > 0) {
    write(STDOUT_FILENO, buffer, bytes_read);
  }
  #endif 

  write(fd2,"salih ",16);

  close(fd1);
  close(fd2);

  return 0;
}



