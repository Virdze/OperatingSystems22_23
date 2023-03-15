#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    int exec_return = execlp("ls","-l",NULL);
    return 0;
}