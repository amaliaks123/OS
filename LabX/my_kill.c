#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    printf("Child received signal: %d\n", sig);
}

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        // Child process
        signal(SIGUSR1, handler);  // Handle the signal
        pause();  // Wait for signal
    } else if (pid > 0) {
        // Parent process
        sleep(1);  // Ensure child is waiting
        kill(pid, SIGUSR1);  // Send signal to child
        wait(NULL);  // Wait for child to finish
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
