#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
    int fd[2];
    pid_t pid;
    int status;

    if (pipe(fd) < 0){
        perror("Error creating pipe!\n");
        _exit(-1);
    }

    if ((pid = fork()) < 0 ){
        perror("Error using fork()!\n");
        _exit(-1);
    }
    else if (!pid){
        close(fd[1]);
        ssize_t readedBytes;
        int buf;
        while ((readedBytes = read(fd[0], &buf, sizeof(buf))) > 0){
            printf("Readed Number: %d\n", buf);
        }
        close(fd[0]);
        _exit(0);
    }
    else {
        int msg = 999;
        close(fd[0]);
        write(fd[1],&msg,sizeof(msg));
        close(fd[1]);
        pid_t terminated_pid = wait(&status);
        printf("Filho terminou com código (%d).\n", WEXITSTATUS(status));
    }
    return 0;
}