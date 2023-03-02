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

    for(int i = 1; i <= 10;i++){
        if((pid = fork()) < 0){
            perror("Error using fork()!\n");
            _exit(-1);
        }else if(!pid){
        printf("(SON %d) My pid: %d\n", i, getpid());
        printf("(SON %d) My father pid: %d\n", i, getppid());
        
        _exit(i);
        }
    }
    for(int i = 1; i <= 10; i++){
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)){
                printf("(FATHER) Process (%d) finished with code %d\n", terminated_pid, WEXITSTATUS(status));
        }
    }
    return 0;
}