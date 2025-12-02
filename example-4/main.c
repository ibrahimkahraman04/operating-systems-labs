#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int old_fd, new_fd;

    // Open a file "dup_test.txt"
    // Create it if it doesn't exist, Read/Write mode
    old_fd = open("dup_test.txt", O_RDWR | O_CREAT, 0777);

    if (old_fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    printf("Original File Descriptor: %d\n", old_fd);

    // Use dup() to create a copy of the file descriptor
    // It automatically assigns the lowest available file descriptor number
    new_fd = dup(old_fd);

    printf("Duplicated File Descriptor (using dup): %d\n", new_fd);

    // Use dup2() to create a copy with a specific descriptor number (e.g., 7)
    // If 7 was open, it would be closed first.
    int specific_fd = 7;
    dup2(old_fd, specific_fd);

    printf("Duplicated File Descriptor (using dup2): %d\n", specific_fd);

    // Close all descriptors
    close(old_fd);
    close(new_fd);
    close(specific_fd);

    return 0;
}