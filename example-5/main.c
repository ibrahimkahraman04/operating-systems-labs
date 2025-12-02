#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t q;

    printf("Before fork\n");

    // Create a child process
    q = fork();

    if (q < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } 
    else if (q == 0) {
        // This block is executed by the CHILD process
        printf("I am child having id %d\n", getpid());
        printf("My parent's id is %d\n", getppid());
    } 
    else {
        // This block is executed by the PARENT process
        // q holds the PID of the child
        printf("I am parent having id %d\n", getpid());
        printf("My child's id is %d\n", q);
    }

    printf("Common\n"); // This line is executed by BOTH processes

    return 0;
}