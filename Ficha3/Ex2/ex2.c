#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
    int status;
    pid_t pid;

    if((pid = fork()) < 0){
        perror("Error using fork()!\n");
        _exit(-1);
    }
    else if (!pid) {
        int exec_return = execlp("ls","-l",NULL);
        _exit(1);
    }
    else{
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status))
            printf("Filho (%d) terminou execução do comando com sucesso (%d)\n",terminated_pid,WEXITSTATUS(status));
    }
    return 0;
}