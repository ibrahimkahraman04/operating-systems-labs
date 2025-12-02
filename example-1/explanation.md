## 💻 C Code Explanation: `unistd.h` Functions

This is a Markdown file (`.md`) explaining the provided C code snippet, which utilizes the **POSIX standard I/O functions** `write()` and `read()` from the `<unistd.h>` header.

-----

### 📚 Overview

The program demonstrates the basic usage of the **system calls** `write` and `read` for input/output operations, commonly used in Unix-like operating systems. It writes a fixed string to the standard output and then reads user input from the standard input, echoing it back to the standard output.

-----

### 🧱 Code Structure

The code is structured into three functions:

1.  `write_fonksiyonu` (Turkish for "write function")
2.  `read_fonksiyonu` (Turkish for "read function")
3.  `main`

#### 1\. `write_fonksiyonu(int m)`

  * **Purpose:** Writes the string "Hello" to the standard output and prints the return value of the `write()` call.
  * **Implementation Details:**
      * `m = write(1, "Hello", 5);`
          * The `write()` system call is used:
              * **First argument (`1`):** This is the **file descriptor** for **Standard Output** (`STDOUT_FILENO`). This is where the data will be written.
              * **Second argument (`"Hello"`):** This is the **buffer** containing the data to be written.
              * **Third argument (`5`):** This is the **number of bytes** to write (the length of "Hello").
          * The return value (`m`) is the **number of bytes actually written**. On success, this should be 5.
      * `printf("\nvalue of n is %d\n", m);`
          * Prints the value stored in `m` (the number of bytes written). **Note:** The variable name in the `printf` is `n`, which is technically incorrect based on the function's parameter name, but it prints the value of `m` which holds the return value of `write`. The compiler would use the value of the local variable `m`.
      * **Return:** Returns `0`. The parameter `m` is passed by value and is not used as an input; it's used as an output variable for the `write` call.

#### 2\. `read_fonksiyonu(int n)`

  * **Purpose:** Reads up to 30 bytes of data from the standard input and writes (echoes) the read data back to the standard output.
  * **Implementation Details:**
      * `char b[30];`
          * Declares a **buffer** `b` of 30 characters to store the input.
      * `n = read(0, b, 30);`
          * The `read()` system call is used:
              * **First argument (`0`):** This is the **file descriptor** for **Standard Input** (`STDIN_FILENO`). This is where the data will be read from.
              * **Second argument (`b`):** This is the **buffer** where the read data will be stored.
              * **Third argument (`30`):** This is the **maximum number of bytes** to read.
          * The return value (`n`) is the **number of bytes actually read**.
      * `write(1, b, n);`
          * The read data in buffer `b` is written back to Standard Output (`1`).
          * Crucially, it uses `n` (the number of bytes read) as the size argument, ensuring only the valid input and not any junk data beyond the input is written.
      * **Return:** Returns `0`. The parameter `n` is passed by value and is not used as an input; it's used as an output variable for the `read` call.

#### 3\. `main()`

  * **Purpose:** The entry point of the program. It calls the two I/O functions sequentially.
  * **Implementation Details:**
      * `int n; int m;`
          * Declares variables that are **uninitialized** before being passed to the functions. This is generally poor practice, but since the functions immediately overwrite these parameters with the `write`/`read` return values, it doesn't cause a runtime error here.
      * `write_fonksiyonu(n);`
          * Calls the write function.
      * `read_fonksiyonu(m);`
          * Calls the read function.
      * **Return:** Returns `0` to the operating system, indicating successful execution.

-----

### ⚙️ How to Compile and Run

1.  **Save:** Save the code as a file, e.g., `io_test.c`.
2.  **Compile (using GCC):**
    ```bash
    gcc io_test.c -o io_test
    ```
3.  **Run:**
    ```bash
    ./io_test
    ```

-----

### 🔬 Expected Output/Behavior

1.  The `write_fonksiyonu` executes first.
2.  It prints: `Hello`
3.  It prints the return value of `write`: `value of n is 5`
4.  The `read_fonksiyonu` executes next and **waits for user input**.
5.  *\[User types input and presses ENTER]*
6.  The program reads the input (including the newline character from ENTER).
7.  The program echoes the input immediately after the `read` operation.
8.  The program exits.

**Example execution:**

```
Hello
value of n is 5
This is my input  <-- User types this and presses ENTER
This is my input
```