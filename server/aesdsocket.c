#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PORT 9000
#define DATA_FILE "/var/tmp/aesdsocketdata"

// Function prototypes
void handle_signal(int sig);
void handle_client(int client_socket);

int main(int argc, char *argv[]) {
    int daemon_mode = 0;

    // Parse command-line arguments
    if (argc > 1 && strcmp(argv[1], "-d") == 0) {
        daemon_mode = 1;
    }

    if (daemon_mode) {
        // Fork and detach for daemon mode
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error forking for daemon mode");
            closelog();
            return -1;
        } else if (pid > 0) {
            // Parent process (exit)
            closelog();
            return 0;
        }

        // Child process (continue)
        setsid(); // Create a new session

        // Redirect standard file descriptors
        int null_fd = open("/dev/null", O_RDWR);
        dup2(null_fd, STDIN_FILENO);
        dup2(null_fd, STDOUT_FILENO);
        dup2(null_fd, STDERR_FILENO);
        close(null_fd);

        // Change working directory to root
        chdir("/");
    }

    // Open syslog for logging
    openlog(NULL, LOG_CONS | LOG_PID, LOG_USER);

    // Create a socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error creating socket");
        closelog();
        return -1;
    }

    // Set up the server address structure
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        close(server_fd);
        closelog();
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) == -1) {
        perror("Error listening for connections");
        close(server_fd);
        closelog();
        return -1;
    }

    // Signal handling
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    while (1) {
        // Accept a connection
        int client_socket = accept(server_fd, NULL, NULL);
        if (client_socket == -1) {
            perror("Error accepting connection");
            continue;
        }

        // Handle the client in a new process
        pid_t child_pid = fork();
        if (child_pid == 0) {
            // In the child process
            close(server_fd); // Close server socket in the child
            handle_client(client_socket);
            exit(0);
        } else if (child_pid > 0) {
            // In the parent process
            close(client_socket); // Close client socket in the parent
        } else {
            perror("Error forking");
            close(client_socket);
        }
    }

    // Cleanup and close server socket
    close(server_fd);

    // ...

    closelog();
    return 0;
}

// Signal handling function
void handle_signal(int sig) {
    if (sig == SIGINT || sig == SIGTERM) {
        syslog(LOG_INFO, "Caught signal, exiting");
        // Additional cleanup and exit logic
        // ...
        exit(0);
    }
}

// Function to handle client connection
void handle_client(int client_socket) {
    // ...

    // Example: Log accepted connection
    syslog(LOG_INFO, "Accepted connection from xxx");

    // Example: Receive data and append to the file
    // ...

    // Example: Send the content of the file back to the client
    // ...

    // Example: Log closed connection
    syslog(LOG_INFO, "Closed connection from xxx");

    // ...

    // Close the client socket
    close(client_socket);
}

