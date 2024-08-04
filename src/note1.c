#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void handler(int signum) {
    printf("Caught signal %d\n", signum);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler;  // Fixed typo here

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Press Ctrl+C to trigger the signal handler\n");
    while (1) {
        // Loop indefinitely to keep the program running
        sleep(1); // Sleep for a second to avoid busy-waiting
    }

    return 0;
}