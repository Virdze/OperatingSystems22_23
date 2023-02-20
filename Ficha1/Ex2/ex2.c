#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <time.h>
#include <math.h>

#define MAX_BUFFER_SIZE 1024

int main(){

    char * buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);

    ssize_t readedBytes;
    
    printf("(!) Usage :\n Click Enter with nothing written to exit.\n");

    while((readedBytes = read(0, buffer, MAX_BUFFER_SIZE)) > 0 && buffer[0] != '\n'){
        write(1,buffer, readedBytes);
    }


    
    return 0;
}