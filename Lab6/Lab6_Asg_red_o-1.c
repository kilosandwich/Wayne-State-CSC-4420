#include<errno.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

/*
 ∗ (100 points)
In the first program, a child will write a string to a pipe and the parent
reads the string from the pipe. (Lab06_Asg_pipe_os.c)
A child executes the ‘env’ system call in the second program. The stdout
of ‘env’ is redirected to stdin of ‘grep’ HOME in the parent.
(Lab6_Asg_red_o.c)
(a) Read the page of pipe and dup2 system calls.
(b) Fill in the blanks in the code provided and make sure it works as the
description above.
(c) Compile the code and make sure it is executable.
(d) Upload the source code.


THIS IS THE FIRST PROGRAM, THE SECOND PROGRAM 
*/


int main(void) {
    pid_t childpid;
    int fd[2];
    
    if (pipe(fd) == -1) { /* setup a pipe */
        
        perror("Failed to setup pipeline");
        return 1;
    }
    if ((childpid = fork()) == -1) { /* fork a child */
        perror("Failed to fork a child");
        return 1;
    }
    if (childpid == 0) {/* env is the child */
        
        if (dup2(fd[1],STDOUT_FILENO) == -1)
            perror("Failed to redirect stdout of env");
        else if (close(fd[0] == -1 || close(fd[1]) == -1)) /* close unused file descriptor */
            perror("Failed to close extra pipe descriptors on env");
        else {
            execl("/usr/bin/env", "env", NULL); /* execute env */
            perror("Failed to exec env");
        }
        return 1;
    }
    if (dup2(fd[0], STDIN_FILENO) == -1)
    /* grep is the parent */
        perror("Failed to redirect stdin of grep");
    else if (close(fd[0]) == -1 || close(fd[1]) == -1)
        perror("Failed to close extra pipe file descriptors on grep");
    else {
        execl("/bin/grep", "grep", "HOME", NULL); /*execute "grep HOME"*/
        perror("Failed to exec grep");
    }
    return 1;
}
