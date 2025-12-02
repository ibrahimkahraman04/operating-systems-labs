## 🔍 C Code Explanation: File Seeking with `lseek()`

This Markdown file (`.md`) explains the provided C code, which demonstrates how to manipulate the file pointer within an open file using the `lseek()` system call before reading data.

-----

### 📚 Overview

This program showcases the use of the `lseek()` system call to explicitly control the **file offset** (or "pointer") within a file named **`seeking`**. It opens the file, moves the pointer 10 bytes from the beginning, reads 10 bytes from that new position, and prints the read content to the console.

The use of `lseek()` is crucial for **random access** file operations, allowing a program to read or write data at any specific location within a file, rather than just sequentially.

-----

### 🧱 System Calls and Headers

The code uses the following key system calls and headers:

| System Call/Header | Purpose |
| :--- | :--- |
| `<unistd.h>` | Provides `read()`, `write()`, `close()`, and **`lseek()`**. |
| `<fcntl.h>` | Provides the file control function `open()` and flags (`O_RDWR`). |
| `<sys/types.h>`, `<sys/stat.h>` | Provide necessary types like `off_t`. |
| `<stdio.h>` | Provides standard I/O functions like `printf()` and `perror()`. |
| `<stdlib.h>` | Provides the general utilities like `exit()`. |

-----

### 🔬 Detailed Code Breakdown

#### 1\. Initialization

```c
int n, f;
off_t f1; 
char buff[10];
```

  * `f`: An integer variable to store the **File Descriptor** returned by `open()`.
  * `n`: An integer variable to store the **number of bytes** read by `read()`.
  * `f1`: A variable of type `off_t` (an integer type capable of representing file sizes and offsets) used to store the **new file offset** returned by `lseek()`.
  * `buff[10]`: A character buffer to temporarily hold the 10 bytes of data read from the file.

#### 2\. Opening the File

```c
f = open("seeking", O_RDWR);

if (f < 0) {
    perror("Dosya açma hatası"); // File open error
    exit(1);
}
```

  * `open("seeking", O_RDWR)`: Attempts to open the file named **`seeking`** with **read and write access** (`O_RDWR`).
  * **Error Handling:** If the file does not exist or the program lacks permission, `open()` returns `-1`. The `perror()` function prints the system error message along with the custom message ("Dosya açma hatası"). The program then exits.

#### 3\. Setting the File Pointer with `lseek()`

```c
f1 = lseek(f, 10, SEEK_SET);

if (f1 == (off_t)-1) {
    perror("Lseek hatası"); // Lseek error
    close(f);
    exit(1);
}
```

  * `lseek(f, 10, SEEK_SET)`: This is the core operation, manipulating the file pointer:
      * **First argument (`f`):** The file descriptor of the open file.
      * **Second argument (`10`):** The **offset** value in bytes.
      * **Third argument (`SEEK_SET`):** The **whence** (reference point) flag. `SEEK_SET` means the offset is calculated from the **beginning of the file (offset 0)**.
  * **Result:** The file pointer is moved exactly 10 bytes from the start.
  * The return value (`f1`) is the **new file offset** (which will be 10 on success).
  * **Error Handling:** If `lseek()` fails (e.g., trying to seek before the start of the file), it returns `(off_t)-1`. The program handles this error and exits.

#### 4\. Reporting the Pointer Position

```c
printf("Pointer şu an %ld. pozisyonda\n", (long)f1); // Pointer is currently at %ld position
```

  * This line confirms the new position of the file pointer by printing the value returned by `lseek()` (`f1`). The offset is cast to `long` for correct printing with the `%ld` format specifier.

#### 5\. Reading Data

```c
n = read(f, buff, 10);

if (n < 0) {
    perror("Okuma hatası"); // Read error
    close(f);
    exit(1);
}
```

  * `read(f, buff, 10)`: Reads up to 10 bytes from the file.
      * Because the file pointer was just set to position 10, the read operation starts **from the 11th byte** of the file.
      * The data is stored in the `buff` buffer.
      * The actual number of bytes read is stored in `n`.
  * **Error Handling:** Checks for read errors (e.g., I/O failure) and exits if one occurs.

#### 6\. Writing Output and Cleanup

```c
write(STDOUT_FILENO, buff, n); 
write(STDOUT_FILENO, "\n", 1);
close(f);
```

  * `write(STDOUT_FILENO, buff, n)`: Writes the content read into the `buff` back to the **Standard Output** (`STDOUT_FILENO`, which is file descriptor `1`), using `n` to ensure only the valid read bytes are printed.
  * `write(STDOUT_FILENO, "\n", 1)`: Prints a newline character for clean formatting.
  * `close(f)`: Closes the file descriptor, releasing the resource.
  * `return 0`: Exits the program successfully.

-----

### 📝 Key Concept: `lseek()` Reference Points

The third argument to `lseek()` (`whence`) determines the reference point for the file offset:

| `whence` | Description |
| :--- | :--- |
| **`SEEK_SET`** | Sets the offset relative to the **beginning** of the file (offset 0). |
| **`SEEK_CUR`** | Sets the offset relative to the **current position** of the file pointer. |
| **`SEEK_END`** | Sets the offset relative to the **end** of the file. |