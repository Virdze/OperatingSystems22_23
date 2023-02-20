#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXBUFSIZE 10

char file_buffer[10];
int next_position = 0;
int last_read_bytes = 0;

int readch(int fd, char *buf){
    //se nao tiver mais dados disponiveis:
    if(next_position == last_read_bytes) {
        int bytes = 0;
        if ((bytes = read(fd, file_buffer, 10)) < 1)
            return 1;
        next_position = 0;
        last_read_bytes = bytes;
    }
    *buf = file_buffer[next_position];
    next_position++;
    //  otherwise
    //  :. escrever um caracter em buf e atualizar estado do buffer(next_postion++)


    return 0;
}

ssize_t readln(int fd, char *line, size_t size) {
    int next_pos = 0;
    int read_bytes = 0;

    while(next_pos < size && readch(fd,line + next_pos) > 0){
        read_bytes++;
        if(line[next_pos++] == '\n')
            break;
    }
    return next_pos;
}

int main(char argc, char* argv[]) {
    char buffer[MAXBUFSIZE];
    int bytes_read = 0;

    int fd = open(argv[1],O_RDONLY);

    while ((bytes_read = readln(fd, buffer, MAXBUFSIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    close(fd);

    return 0;
}
