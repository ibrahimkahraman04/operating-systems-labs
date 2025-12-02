## 🧵 C Code Explanation: Simple Multithreading with `pthread`

This Markdown file (`.md`) explains the provided C code, which demonstrates the basics of **multithreading** using the POSIX Threads library (`pthread`).

-----

### 📚 Overview

The program utilizes the `pthread` library to create a **separate thread of execution** within the main process. The main process creates a new thread to run a specific function (`thread\_function`). It then **waits** for the new thread to finish its work before continuing its own execution. This ensures sequential execution between the thread's task and the main program's subsequent task.

-----

### 🧱 System Calls and Headers

The code relies on the following key system calls and headers:

| Header | Purpose |
| :--- | :--- |
| `<stdio.h>` | Provides standard I/O functions like `printf()`. |
| `<unistd.h>` | Provides the **`sleep()`** function for pausing execution. |
| `<pthread.h>` | Provides the POSIX Threads API, including **`pthread\_t`**, **`pthread\_create()`**, and **`pthread\_join()`**. |

-----

### 🔬 Detailed Code Breakdown

#### 1\. Global Variables and Function Prototypes

```c
void *thread_function(void *arg);
int i, j;
```

  * **`thread_function`**: The prototype for the function that will be executed by the new thread. It must have the signature `void *(*)(void *)`.
  * **`i` and `j`**: Global integer variables used as loop counters in the thread and main functions, respectively.

#### 2\. Main Function (`main()`)

```c
int main()
{
    pthread_t a_thread;

    pthread_create(&a_thread, NULL, thread_function, NULL);
    pthread_join(a_thread, NULL);

    printf("Inside Main Program\n");

    for (j = 20; j < 25; j++)
    {
        printf("%d\n", j);
        sleep(1);
    }

    return 0;
}
```

  * **`pthread_t a_thread`**: Declares a variable to hold the **Thread ID (TID)** of the newly created thread.
  * **`pthread_create(...)`**: This call creates the new thread:
      * **First argument (`&a_thread`)**: Pointer to the `pthread\_t` variable where the new thread ID will be stored.
      * **Second argument (`NULL`)**: Specifies thread attributes (using default attributes here).
      * **Third argument (`thread_function`)**: The function pointer to the routine the thread will execute.
      * **Fourth argument (`NULL`)**: The argument to be passed to `thread\_function`.
  * **`pthread_join(a_thread, NULL)`**: This is the **synchronization point**. The main thread **blocks** (waits) here until the thread specified by `a\_thread` terminates.
  * **Main Loop**: Because of `pthread\_join()`, the `printf("Inside Main Program\n")` and the subsequent loop run **only after** `thread\_function` has completed its execution (which takes 5 seconds due to the `sleep(1)` inside the loop).
  * The main loop prints numbers 20 through 24, pausing for 1 second between each print.

#### 3\. Thread Function (`thread_function()`)

```c
void *thread_function(void *arg)
{
    printf("Inside Thread\n");

    for (i = 0; i < 5; i++)
    {
        printf("%d\n", i);
        sleep(1);
    }

    return NULL;
}
```

  * This function is the **entry point** for the new thread.
  * It immediately prints an identifying message.
  * It executes a loop, printing numbers 0 through 4, pausing for 1 second between each print.
  * **Termination**: When the function reaches `return NULL;`, the thread terminates, signaling the waiting parent (the main thread) via `pthread\_join()`.

-----

### 📝 Execution Flow

Due to the use of `pthread\_join()`, the execution of the program is guaranteed to be sequential:

1.  **Main** calls `pthread\_create()`.
2.  **Thread** starts running.
3.  **Main** immediately calls `pthread\_join()` and **waits**.
4.  **Thread** prints "Inside Thread".
5.  **Thread** executes its loop (prints 0, 1, 2, 3, 4, taking 5 seconds total).
6.  **Thread** returns and terminates.
7.  **Main** resumes from `pthread\_join()`.
8.  **Main** prints "Inside Main Program".
9.  **Main** executes its loop (prints 20, 21, 22, 23, 24, taking 5 seconds total).
10. **Main** terminates the program.