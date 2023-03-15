#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
    pid_t pid;
    pid_t pids[argc - 1];
    int status;

    for(int i = 1; i < argc; i++){
        if ((pid = fork()) < 0){
            perror("Error using fork()!\n");
            _exit(-1);
        } else if(!pid) {
            int exec_return = execlp(argv[i],argv[i],NULL);
            _exit(0);
        } else pids[i-1] = pid;
    }

    for(int i = 0; i < argc-1;i++ ){
        pid_t terminated_pid = waitpid(pids[i],&status,0);
        if(WIFEXITED(status)){
            printf("Filho (%d) terminou execução do comando com sucesso!\n",terminated_pid);
        }
    }
    return 0;

}