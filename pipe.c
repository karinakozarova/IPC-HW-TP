#include <stdio.h>
#include <fcntl.h>              
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{   
    char msg[1024],ch;
    int pipefd[2];
    pipe(pipefd);
    printf("ENTER MESSAGE:\n");

    pid_t pid = fork();

    if (pid == 0){
        close(pipefd[1]);
        for(;;) while(read(pipefd[0], &ch, 1) > 0) write(STDOUT_FILENO, &ch, 1);
    }
    else{
        for(;;){
            close(pipefd[0]);
            fgets(msg, sizeof(msg), stdin);
            printf("YOUR MESSAGE:\n");
            write(pipefd[1], msg, strlen(msg));
        }   
    }
}