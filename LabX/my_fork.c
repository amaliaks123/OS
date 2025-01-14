#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    for (int i = 0; i < 3; i++) {
        pid = fork();
        if (pid == 0) {
            printf("Child PID: %d\n", getpid());
            break;
        }
        else if (pid > 0) {
            printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
            wait(NULL);  // Parent waits for child to finish
        } else {
            perror("Fork failed");
            return 1;
        }
    }

    return 0;
}
