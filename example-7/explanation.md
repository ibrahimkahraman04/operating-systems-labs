## 👻 C Code Explanation: Demonstrating the Orphan Process and the `init` Adoption

This Markdown file (`.md`) explains the provided C code, which demonstrates how a child process becomes an **orphan** when its parent terminates before it does, leading to the child being **adopted** by the operating system's main process.

-----

### 📚 Overview

The program utilizes the `fork()` system call to create a parent and a child process. The core functionality is achieved by making the **parent process terminate quickly** while the **child process pauses** using `sleep(5)`. This sequence ensures that the child is still running when its parent exits, causing the child to become an orphan. The operating system then immediately assigns the orphan to the **`init` process** (or its modern equivalent, PID 1 or the system manager).

-----

### 🧱 System Calls and Headers

The code relies on the following key system calls and headers:

| System Call/Header | Purpose |
| :--- | :--- |
| `<unistd.h>` | Provides **`fork()`** (process creation), **`getpid()`** (get current process ID), **`getppid()`** (get parent process ID), and **`sleep()`** (pause execution). |
| `<sys/types.h>` | Provides necessary data types, such as **`pid_t`** (Process ID type). |
| `<stdio.h>` | Provides standard I/O functions like `printf()` and `perror()`. |

-----

### 🔬 Detailed Code Breakdown

#### 1\. Process Creation with `fork()`

```c
pid_t id_val;
id_val = fork();

if (id_val < 0) {
    perror("Process creation failed");
    return 1;
}
```

  * **`id_val`**: Stores the return value of `fork()`: the **child's PID** in the parent, and **0** in the child itself.
  * If `fork()` fails (returns `< 0`), an error is printed, and the program exits.

#### 2\. Execution Path: The Parent Process

```c
if (id_val > 0) {
    // --- PARENT ---
    printf("[Parent] Running. My PID: %d, Created Child: %d\n", getpid(), id_val);
    
    // Parent bitiyor (Child hala calisirken)
    printf("[Parent] My work is done. Terminating execution now.\n");
}
```

  * This block is executed only by the **parent process** (where `id_val > 0`).
  * It prints its own PID (`getpid()`) and the PID of the child it created (`id_val`).
  * The parent executes quickly and immediately reaches the end of its `if` block, then proceeds to `return 0;`, thus **terminating** without waiting for the child.

#### 3\. Execution Path: The Child Process

```c
else {
    // --- CHILD ---
    // Baslangicta normal ebeveyne sahip
    printf("[Child] Started. My PID: %d, Current Parent: %d\n", getpid(), getppid());

    printf("[Child] Pausing for 5 seconds to let parent finish...\n");
    sleep(5);

    // Uyandiginda parent ölmüş olmalı, isletim sistemi tarafindan evlat edinilmeli
    printf("[Child] Resumed. My PID: %d, New Parent (Adopter): %d\n", getpid(), getppid());
}
```

  * This block is executed only by the **child process** (where `id_val == 0`).
  * **Initial State**: The child prints its own PID and its **original parent's PID** (`getppid()`).
  * **Pausing**: The child calls `sleep(5)`, which forces it to pause its execution for 5 seconds. During this time, the parent process finishes and terminates.
  * **Orphan Status and Adoption**: When the child resumes, it calls `getppid()` again. Because its original parent has died, the operating system kernel re-parents the child to the **`init` process** (PID 1). The output confirms this change in the parent's PID.

-----

### 📝 Expected Execution Sequence and Output

The output sequence will be deterministic in terms of process state changes:

1.  The initial process executes `fork()`.
2.  The **Parent** runs first (or the Child runs first, but the Parent is generally faster since it has less work).
3.  The **Parent** prints its PID, prints the child's PID, and terminates immediately.
4.  The **Child** prints its initial parent's PID.
5.  The **Child** pauses for 5 seconds (`sleep(5)`).
6.  The **Parent** is now dead. The kernel assigns the child to PID 1 (`init`).
7.  The **Child** resumes, calls `getppid()`, and prints the **new parent's PID** (which will be **1** on most Linux/Unix systems), confirming the adoption.

**Conceptual Output Flow:**

```
[Parent] Running. My PID: 12345, Created Child: 12346
[Parent] My work is done. Terminating execution now.
[Child] Started. My PID: 12346, Current Parent: 12345
[Child] Pausing for 5 seconds to let parent finish...
(5 second pause)
[Child] Resumed. My PID: 12346, New Parent (Adopter): 1
```