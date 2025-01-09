#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    child_pid = fork();

    if (child_pid == -1) {
        // Fork failed
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process id: %d\n", getpid());
        printf("Child's parent process id: %d\n", getppid());
    } else {
        // Parent process
        printf("Parent process id: %d\n", getpid());
        printf("Parent's child process id: %d\n", child_pid);
    }

    return 0;
}
