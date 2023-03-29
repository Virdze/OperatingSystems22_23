#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 512

int main(int argc, char *argv[]){
    int fifo;

    if((fifo = mkfifo("fifo", 0600)) < 0){
        perror("Error creating fifo!\n");
        _exit(-1);
    }

    char * buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    
    printf("Insert anything to end and unlink the fifo created!\n");
    read(0, buffer, MAX_BUFFER_SIZE); 

    unlink("fifo");
    return 0;
}