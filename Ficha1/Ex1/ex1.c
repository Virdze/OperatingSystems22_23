#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <time.h>
#include <math.h>

#define MAX_READ_SIZE 1024

int main(int agrc, char * argv[]){

    int fd_read
        ,fd_write;

    if((fd_read = open(argv[1], O_RDONLY)) < 0 ){
        perror("Error opening read file descriptor");
        return 1;
    }

    if((fd_write = open(argv[2], O_RDONLY | O_WRONLY | O_CREAT | O_TRUNC, 0640)) < 0){
        perror("Error opening write file descriptor");
        return 1;
    }

    char * buffer = malloc(sizeof(char) * MAX_READ_SIZE);

    ssize_t readedBytes;
    time_t startTime = clock();

    while((readedBytes = read(fd_read, buffer, MAX_READ_SIZE)) > 0){
        write(fd_write, buffer, readedBytes);
    }

    time_t finish_time = clock();

    close(fd_read);
    close(fd_write);
    
    float time = (finish_time - startTime) * pow(10,-9);
    
    printf("Copied file sucessfuly!\nTime: %f",time);

    return 0;
 
}
