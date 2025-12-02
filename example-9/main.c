#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t new_pid;

    printf("System active. Attempting to launch external program...\n");

    new_pid = fork();

    if (new_pid < 0) {
        perror("Fork error");
        return 1;
    }

    if (new_pid > 0) {
        printf("Parent (ID: %d) waiting for child termination...\n", getpid());
        
        wait(NULL);
        
        printf("Parent: Child task finished. Exiting.\n");
    } 
    else {
        printf("Child (ID: %d) replacing memory with 'ls -l'...\n", getpid());

        execl("/bin/ls", "ls", "-l", NULL);

        perror("Exec failed");
        exit(1);
    }

    return 0;
}