#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <time.h>
#include <math.h>

#define MAX_BUFFER_SIZE 1024


ssize_t readln(int fd, char * line, size_t size){
    int i = 0;
    ssize_t readedBytes;
    char c;
    while(i < size && (readedBytes = read(fd, line, size) > 0) && line[i] != '\n'){
        i+= readedBytes;
    }   
    return i;
}


int main (int argc, char * argv[]){
    int fd_write;
    if((fd_write = open(argv[1], O_RDONLY | O_WRONLY | O_CREAT | O_TRUNC, 0640)) < 0){
        perror("Error opening write file descriptor");
        return 1;
    }

    ssize_t readedBytes;

    char * buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);

    while( (readedBytes = readln(STDIN_FILENO, buffer, MAX_BUFFER_SIZE)) > 0){
        write(fd_write,&c,readedBytes);
    }

    close(fd_write);

    return 0;
}