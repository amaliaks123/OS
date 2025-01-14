#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char message[] = "Hello from parent";

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        // Child process
        close(pipefd[1]);  // Close write end
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received message: %s\n", buffer);
        close(pipefd[0]);
    } else if (pid > 0) {
        // Parent process
        close(pipefd[0]);  // Close read end
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
        wait(NULL);  // Wait for child to finish
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
