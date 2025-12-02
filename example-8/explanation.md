## 🧟 C Code Explanation: Demonstrating the Zombie Process

This Markdown file (`.md`) explains the provided C code, which demonstrates how a child process becomes a **zombie process** when the parent process fails to properly collect its exit status.

-----

### 📚 Overview

The program creates a child process using `fork()`. The core behavior demonstrated here is achieved by making the **child process terminate immediately** while the **parent process pauses** for a significant duration (`sleep(10)`).

When a child process terminates, the operating system releases most of its resources, but its **Process Descriptor (PCB)**, containing its exit status, must remain in the kernel's process table until the parent retrieves this status using a `wait()` family function. Because the parent process in this code sleeps and does **not** call `wait()`, the finished child process remains in a terminated state, known as a **zombie process** or `<defunct>`.

-----

### 🧱 System Calls and Headers

The code relies on the following key system calls and headers:

| System Call/Header | Purpose |
| :--- | :--- |
| `<unistd.h>` | Provides **`fork()`** (process creation) and **`sleep()`** (pause execution). |
| `<sys/types.h>` | Provides necessary data types, such as **`pid_t`** (Process ID type). |
| `<sys/wait.h>` | Provides the declaration for `wait()` functions, although none are used here, leading to the zombie state. |
| `<stdio.h>` | Provides standard I/O functions like `printf()`. |

-----

### 🔬 Detailed Code Breakdown

#### 1\. Process Creation with `fork()`

```c
pid_t p;
p = fork();
// ... error handling omitted for brevity ...
```

  * **`p`**: Stores the return value of `fork()`: the **child's PID** in the parent, and **0** in the child itself.

#### 2\. Execution Path: The Child Process

```c
if (p == 0) {
    printf("I am child having PID: %d\n", getpid());
    printf("My parent PID is: %d\n", getppid());
    // Child terminates immediately after printing
}
```

  * This block is executed only by the **child process**.
  * The child prints its PID and its parent's PID.
  * Since there is no further code in this block, the child quickly reaches `return 0;` at the end of `main()` and **terminates**.
  * **ZOMBIE CREATION**: Upon termination, the child process enters the **zombie state** because its parent process is still active (sleeping) and has **not** called `wait()` to collect the child's exit status.

#### 3\. Execution Path: The Parent Process

```c
else {
    sleep(10);
    printf("I am parent having PID: %d\n", getpid());
    printf("My child PID is: %d\n", p);
    // Parent terminates after sleeping
}
```

  * This block is executed only by the **parent process** (where `p` holds the child's PID).
  * **`sleep(10)`**: The parent process halts its execution for 10 seconds. This delay ensures the child has time to terminate and enter the zombie state while the parent is still running.
  * After the pause, the parent wakes up, prints its own PID and the child's PID, and then terminates.

### 📝 Demonstrating the Zombie State

To observe the zombie process, one must compile and run the code, and quickly use a system monitoring tool (like `ps`) in a separate terminal *before the 10 seconds of sleep are over*:

```bash
# In Terminal 1 (Run the program)
./a.out &

# In Terminal 2 (Quickly check process status)
ps -l | grep a.out
```

**Expected `ps` output during the 10-second sleep:**

| PID (Child) | TTY | STAT | COMMAND |
| :--- | :--- | :--- | :--- |
| 12346 | pts/0 | **Z** | ./a.out \<defunct\> |
| 12345 | pts/0 | S | ./a.out |

The `STAT` column for the child process will show **`Z`** (Zombie), confirming that the process has terminated but is still occupying a slot in the process table. Once the parent terminates, the zombie is cleaned up by the `init` process (or its equivalent).