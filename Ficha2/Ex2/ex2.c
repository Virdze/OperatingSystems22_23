#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h>


int main(int argc, char * argv[]){
    int status;
    pid_t pid;

    if((pid = fork()) < 0){
        perror("Error using fork()!\n");
        _exit(-1);
    }
    else if(!pid){
        printf("(SON) My pid: %d\n", getpid());
        printf("(SON) My father pid: %d\n", getppid());
        
        _exit(0);
    }
    else {
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status))
            printf("(FATHER) Processo filho (%d) terminou com sucesso!\n", terminated_pid);
            printf("(FATHER) My father pid: %d\n",getppid());
    }
    return 0;
}
