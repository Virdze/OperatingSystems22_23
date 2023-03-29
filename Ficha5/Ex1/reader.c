#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 512

int main(int argc, char *argv[]){
    int fifo_fd; 

    if((fifo_fd = open("fifo", O_RDONLY)) < 0){
        perror("Error opening write end from fifo\n");
        _exit(-1);
    }

    ssize_t readedBytes;
    char * buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);


    while((readedBytes = read(fifo_fd, buffer, MAX_BUFFER_SIZE)) > 0 && buffer[0] != '\n'){
        write(1, buffer, readedBytes);
    }

    close(fifo_fd);
    return 0;
}