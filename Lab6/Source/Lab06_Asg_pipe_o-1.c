#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define BUFSIZE 10
int main(void) {
    char bufin[BUFSIZE] = "empty";
    char bufout[] = "hello";
    int bytesin;
    pid_t childpid;
    int fd[2];
    if (---------) { /* create a pipe */
        perror("Failed to create the pipe");
        return 1;
    }
    bytesin = strlen(bufin);
    childpid = fork();
    if (---------) {
        perror("Failed to fork");
        return 1;
    }
    if (---------)
    /* child code */
        write(----, bufout, strlen(bufout)+1);
    else
    /* parent code */
        bytesin = read(----, bufin, BUFSIZE);
    fprintf(stderr, "[%ld]:my bufin is {%.*s}, my bufout is {%s}\n", (long)getpid(), bytesin, bufin, bufout);
    return 0;
}
