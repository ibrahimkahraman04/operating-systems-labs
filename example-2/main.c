#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {
    int n, fd;
    char buffer[50];

    // Prompt user for input
    write(1, "Enter text to append to file: ", 30);

    // Read from Standard Input (Keyboard) -> File Descriptor 0
    n = read(0, buffer, 50);

    // Open the file "target.txt"
    // O_CREAT: Create the file if it doesn't exist.
    // O_WRONLY: Open for writing only.
    // O_APPEND: Append new data to the end of the file.
    // 0644: File permissions (rw-r--r--)
    fd = open("target.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);

    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    // Write the read buffer into the file
    write(fd, buffer, n);

    // Close the file descriptor
    close(fd);

    return 0;
}