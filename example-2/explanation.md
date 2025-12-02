## 💾 C Code Explanation: File I/O with `open`, `read`, and `write`

This Markdown file (`.md`) explains the provided C code, which uses standard **POSIX system calls** to read input from the user and append it to a specified file.

-----

### 📚 Overview

The program demonstrates fundamental **file input/output (I/O)** operations in a Unix-like environment. Specifically, it uses the `read()` function to capture user input from the console and the `open()`, `write()`, and `close()` functions to manage and append that data to a file named **`target.txt`**.

-----

### 🧱 System Calls and Headers

The program relies on several system calls and standard functions, requiring the following headers:

  * **`<unistd.h>`:** Provides access to the POSIX operating system API, including the `read()`, `write()`, and `close()` system calls.
  * **`<fcntl.h>`:** Provides file control options, including the flags used by `open()` (e.g., `O_CREAT`, `O_WRONLY`, `O_APPEND`).
  * **`<sys/types.h>`, `<sys/stat.h>`:** Provide data types and structures for file status information, used by `open()` to specify permissions.
  * **`<stdio.h>`:** Provides standard I/O functions like `perror()`.

-----

### 🔬 Detailed Code Breakdown

#### 1\. Initialization

```c
int n, fd;
char buffer[50];
```

  * `n`: An integer variable used to store the **number of bytes** read from standard input.
  * `fd`: An integer variable used to store the **File Descriptor** returned by the `open()` system call. A file descriptor is a non-negative integer used by the operating system to track an open file or I/O resource.
  * `buffer[50]`: A character array (buffer) used to temporarily hold the user input, with a maximum capacity of 50 bytes.

#### 2\. Reading User Input

```c
// Prompt user for input
write(1, "Enter text to append to file: ", 30);

// Read from Standard Input (Keyboard) -> File Descriptor 0
n = read(0, buffer, 50);
```

  * **Prompt:** The first `write()` call prints the prompt string to **Standard Output** (file descriptor `1`).
  * **Input:** The `read()` system call is executed:
      * **First argument (`0`):** Specifies the **Standard Input** (`STDIN_FILENO`), which typically represents the keyboard.
      * **Second argument (`buffer`):** The memory location where the read data will be stored.
      * **Third argument (`50`):** The maximum number of bytes to read.
      * The return value (`n`) is the actual number of bytes read (which includes the newline character, `\n`, when the user presses Enter).

#### 3\. Opening the File (`target.txt`)

```c
fd = open("target.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);

if (fd < 0) {
    perror("Failed to open file");
    return 1;
}
```

  * The `open()` system call attempts to access the file **`target.txt`**.
  * **Flags:** The second argument uses a bitwise OR (`|`) to combine several flags, defining the file's behavior:
      * `O_CREAT`: If the file does **not** exist, create it.
      * `O_WRONLY`: Open the file for **writing only**.
      * `O_APPEND`: If the file **does** exist, all subsequent writes will be appended to the end of the file, regardless of the current file offset. This is the key feature of this program.
  * **Permissions (`0644`):** The third argument (only used if `O_CREAT` is specified) sets the file permissions:
      * `0`: Octal notation prefix.
      * `6`: **Owner** has read and write permissions (`rw-`).
      * `4`: **Group** has read-only permission (`r--`).
      * `4`: **Others** have read-only permission (`r--`).
  * **Error Check:** If `open()` fails (e.g., due to permission errors), it returns `-1`. The code checks if `fd < 0`, prints an error message using `perror()`, and exits with a non-zero status code (`1`).

#### 4\. Writing to the File

```c
// Write the read buffer into the file
write(fd, buffer, n);
```

  * The `write()` system call is used again:
      * **First argument (`fd`):** The **File Descriptor** returned by `open()`, pointing to `target.txt`.
      * **Second argument (`buffer`):** The data read from the user.
      * **Third argument (`n`):** The exact number of bytes read from the user, ensuring that only the actual input is written to the file.

#### 5\. Cleanup

```c
// Close the file descriptor
close(fd);

return 0;
```

  * `close(fd)`: Releases the file descriptor, freeing up system resources and ensuring all buffered data is written to the disk.
  * `return 0`: Indicates successful program execution.