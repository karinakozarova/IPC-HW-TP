#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>


int main(){
    char msg[1024],ch;
    int pipefd[2];
    pipe(pipefd);

    printf("ENTER MESSAGE:\n");
    fgets(msg, sizeof(msg), stdin);
    printf("YOUR MESSAGE:\n");
    pid_t pid = fork();

    if(pid == 0){
        close(pipefd[1]);
        while(read(pipefd[0],&ch,1) > 0){
            write(STDOUT_FILENO,&ch,1);
        }
    }else{
        close(pipefd[0]);
        write(pipefd[1],msg,strlen(msg));
    }

    return 0;
}
