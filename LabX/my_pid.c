#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    pid_t pid;
    int file = open("pids.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);

    if (file == -1) {
        perror("Failed to open file");
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        // Child process
        dprintf(file, "Child PID: %d\n", getpid());
    } else if (pid > 0) {
        // Parent process
        dprintf(file, "Parent PID: %d\n", getpid());
        wait(NULL);  // Wait for child to finish
    } else {
        perror("Fork failed");
        return 1;
    }

    close(file);
    return 0;
}
