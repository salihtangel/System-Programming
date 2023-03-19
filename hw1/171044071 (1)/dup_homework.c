#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){

    int fd1 = open("input.txt", O_RDONLY );
    int fd2 = open("output.txt", O_WRONLY | O_CREAT, 0644);

#if 0
    int dup_output_fd = dup2(fd2,STDOUT_FILENO);
        if (dup_output_fd == -1) {
        perror("dup2");
        exit(1);
    }
#endif

    char buffer[1024];
    int bytes_read;


    while( bytes_read = read(fd1,buffer,sizeof(buffer)) > 0 )
    {
        write(dup_output_fd,buffer,bytes_read);
    }

    close(fd1);
    close(fd2);
    close(dup_output_fd);

    return 0;
}