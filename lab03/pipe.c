#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int fd[2];
    size_t size;
    char string[] = "Hello, world!\n";
    pid_t forked_pid;
    char buffer[15];
    if(pipe(fd) < 0)
    {
        printf("Can\'t create pipe\n");
        exit(-1);
    }

    forked_pid = fork();
    if (forked_pid == -1) 
    {   
        printf("Error fork\n");
        exit(-1);
    }
    else if (forked_pid == 0) 
    {   
        //Child proc
        close(fd[0]);
        write(fd[1],string,14);
        exit(-1);
    } 
    else 
    {
        //Parent proc
        close(fd[1]);
        size = read(fd[0],buffer,15);
        fputs(buffer,stdout);
    }

    return 0;
} 