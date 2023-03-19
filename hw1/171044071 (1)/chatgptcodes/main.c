#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(1);
    }

    // Open the input file for reading
    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        exit(1);
    }

    // Open the output file for writing
    int output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        perror("open");
        exit(1);
    }

    // Duplicate the output file descriptor and replace STDOUT_FILENO with the duplicate
    int dup_output_fd = dup2(output_fd, STDERR_FILENO);
    if (dup_output_fd == -1) {
        perror("dup2");
        exit(1);
    }

    // Read from the input file and write to both the console and the output file
    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0) {
        write(dup_output_fd, buffer, bytes_read);
        fflush(stdout); // Flush the output to the./r    console
    }

    // Close the file descriptors
    close(input_fd);
    close(output_fd);
    close(dup_output_fd);

    return 0;
}
