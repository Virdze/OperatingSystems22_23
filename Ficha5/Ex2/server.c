#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 512

int main(int arg, char * argv[]){

    int fifo;

    if((fifo = mkfifo("fifo", 0600)) < 0){
        perror("Error creating fifo!\n");
        _exit(-1);
    }

    int fifo_fd;
    if((fifo_fd = open("fifo", O_RDONLY)) < 0){
        perror("Error opening fifo!\n");
        _exit(-1);
    }

    int file_fd; 
    if((file_fd = open("output.txt", O_WRONLY | O_CREAT | O_APPEND, 0640)) < 0){
        perror("Error opening file descriptor to output file!\n");
        _exit(-1);
    }


    ssize_t readedBytes;
    char * buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    int status;
    pid_t pid;

    while((readedBytes = read(fifo_fd, buffer, MAX_BUFFER_SIZE)) > 0){
        if((pid = fork()) < 0){
            perror("Error using fork()!\n");
            _exit(-1);
        }
        else if(!pid) {
            write(file_fd, buffer, readedBytes);
            _exit(0);
        }
    }

    close(fifo_fd);
    close(file_fd);
    unlink("fifo");

    return 0;
}