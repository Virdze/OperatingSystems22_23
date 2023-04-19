    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <sys/stat.h>

    int main(int argc, char * argv[]){
        
        pid_t pid ;
        pid_t pids[4];
        int status;
        int fd[3][2];
        for(int i = 0; i < 3; i++){
            if(pipe(fd[i]) < 0){
                perror("Error while creating pipe!\n");
                _exit(-1);
            }
        }

        for(int i = 0; i < 4; i++){
            if((pid = fork()) < 0){
                perror("Error using fork!\n");
                _exit(-1);
            }
            else if(!pid){
                if(i == 0){
                    close(fd[0][0]);
                    dup2(fd[0][1],1);
                    close(fd[0][1]);
                    for (int j = 1; j < 4 - 1; j++) {
                        close(fd[j][0]);
                        close(fd[j][1]);
                    }
                    execlp("grep","grep", "-v", "^#", "/etc/passwd", NULL);
                    _exit(-1);
                }else if(i == 1){
                    close(fd[0][1]);
                    dup2(fd[0][0],0);
                    close(fd[0][0]);
                    close(fd[1][0]);
                    dup2(fd[1][1], 1);
                    close(fd[1][1]);
                    for (int j = 0; j < 4 - 1; j++) {
                        if (j != i - 1 && j != i) {
                            close(fd[j][0]);
                            close(fd[j][1]);
                        }
                    }
                    execlp("cut", "cut", "-f7", "-d:",NULL);
                    _exit(-1);
                }else if(i == 2){
                    close(fd[1][1]);
                    dup2(fd[1][0],0);
                    close(fd[1][0]);
                    close(fd[2][0]);
                    dup2(fd[2][1], 1);
                    close(fd[2][1]);
                    for (int j = 0; j < 4 - 1; j++) {
                        if (j != i - 1 && j != i) {
                            close(fd[j][0]);
                            close(fd[j][1]);
                        }
                    }
                    execlp("uniq", "uniq",NULL);
                    _exit(-1);
                }
                else if(i == 3){
                    close(fd[2][1]);
                    dup2(fd[2][0],0);
                    close(fd[2][0]);
                    for (int j = 0; j < 4 - 2; j++) {
                        close(fd[j][0]);
                        close(fd[j][1]);
                }
                    execlp("wc","wc","-l",NULL);
                    _exit(-1);
                }
            }else {
                pids[i] = pid;
            }
        }

        for(int i = 0 ; i < 3; i++){
            close(fd[i][0]);
            close(fd[i][1]);
        }

        for(int i = 0 ; i < 4; i++){
            pid_t terminated_pid = wait(&status);

            if(WEXITSTATUS(status) < 0){
                printf("Something went wrong!\n");
                break;
            }
            else printf("Command runned!\n");
        }
        return 0;
    }