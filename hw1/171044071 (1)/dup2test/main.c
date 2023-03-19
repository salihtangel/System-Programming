#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){

    int fd1 = open("input.txt", O_RDONLY ,0666);
    int fd2 = open("output.txt", O_RDWR | O_CREAT,0666);

    int dup_output_fd = dup2(fd2,STDOUT_FILENO);
        if (dup_output_fd == -1) {
        perror("dup2");
        exit(1);
    }

    char buffer[1024] = {0};
    int bytes_read;

    do {
	bytes_read = read(fd1, buffer, 1024);
        int num_write = write(fd2, buffer, bytes_read);
	if(num_write < 0) {
		printf("There is an error:%d-%s", errno, strerror(errno));
	}
    } while(bytes_read > 0);

    close(fd1);
    close(fd2);
    /*close(dup_output_fd);*/

    return 0;
}
