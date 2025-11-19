#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();   // Create a child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("Child Process (PID=%d) executing 'ls -l' command...\n", getpid());

        // Replace child with 'ls -l'
        execlp("ls", "ls", "-l", NULL);

        // If exec fails:
        perror("exec failed");
        exit(1);
    }
    else {
        // Parent process
        int status;
        printf("Parent Process (PID=%d) waiting for child...\n", getpid());

        wait(&status);   // Wait for child to finish

        if (WIFEXITED(status)) {
            printf("Parent: Child exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child terminated abnormally\n");
        }
    }

    return 0;
}