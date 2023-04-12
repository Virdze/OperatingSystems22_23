#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){
    int input_fd;
    if((input_fd = open("/etc/passwd", O_RDONLY)) < 0){
        perror("Error opening file descriptor!\n");
        _exit(-1);
    }

    int output_fd;
    if((output_fd = open("saida.txt", O_CREAT | O_WRONLY | O_TRUNC,0666)) < 0){
        perror("Error opening file descriptor!\n");
        _exit(-1);
    }

    int error_fd;
    if((error_fd = open("error.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0){
        perror("Error opening file descriptor!\n");
        _exit(-1);
    }

    dup2(input_fd,0);
    close(input_fd);
    dup2(output_fd,1);
    close(output_fd);
    dup2(error_fd,2);
    close(error_fd);

    int exec_return = execlp("wc","wc",NULL);
    return 0;
}