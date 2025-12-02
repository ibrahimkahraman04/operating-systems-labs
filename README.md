🖥️ Operating Systems Laboratory ExercisesThis repository serves as a comprehensive collection of laboratory exercises for the Operating Systems course. It focuses on low-level system programming, process management, file I/O operations, and inter-process communication (IPC) within the Linux environment.All implementations strictly utilize the C programming language and standard POSIX system calls.📚 Table of ContentsProject OverviewRepository StructureExercise List & TopicsCompilation & ExecutionSystem RequirementsProject OverviewThe primary objective of this project is to provide practical implementations of core Operating System concepts. Each module is designed to demonstrate specific system calls and their distinct behaviors in a Linux kernel environment.Key Concepts CoveredProcess Management: fork(), wait(), exec() family, Zombie and Orphan processes.File Management: Low-level I/O using open(), read(), write(), lseek().IPC (Inter-Process Communication): Implementation of anonymous pipe().Repository StructureThe project strictly follows a modular directory hierarchy. Each exercise is encapsulated in its own directory containing the source code, technical documentation, and the compiled binary.Plaintextoperating-systems-labs/
│
├── README.md               # Project documentation
│
├── example-01/             # Process Creation
│   ├── main.c              # Source code
│   ├── explanation.md      # Technical explanation
│   └── app                 # Compiled binary
│
├── example-02/             # Process Synchronization
│   ├── main.c
│   ├── explanation.md
│   └── app
│
├── ... (examples 03 to 09)
│
└── example-10/             # Inter-Process Communication
    ├── main.c
    ├── explanation.md
    └── app
Exercise List & TopicsThe following table details the specific topics and system calls implemented in each exercise.IDModule NameKey Concepts & System CallsStatus01Process Creationfork(), getpid(), getppid()✅02Synchronizationwait(), Process State Management✅03Orphan ProcessParent termination, init adoption✅04Zombie ProcessDefunct processes, Process Table✅05Image Replacementexecl(), Memory Overlay✅06Execution Methodssystem() vs exec() family✅07File I/Oopen(), read(), write(), close()✅08Random Accesslseek(), File Offsets✅09I/O Redirectiondup(), dup2(), STDOUT redirection✅10Communicationpipe(), Unidirectional Data Flow✅Compilation & ExecutionEach module is independent. You must compile the source code within its respective directory using the GCC compiler.Standard Build CommandPer course requirements, the output binary is named app.Bashgcc main.c -o app
Step-by-Step GuideNavigate to the specific exercise folder (e.g., Example 01):Bashcd example-01
Compile the C source code:Bashgcc main.c -o app
Run the application:Bash./app
Note: If permission is denied when trying to run the app, grant execution permissions using: chmod +x appSystem RequirementsTo successfully run these exercises, the following environment is recommended:Operating System: Linux (Ubuntu/Debian recommended) or WSL (Windows Subsystem for Linux).Compiler: GCC (GNU Compiler Collection).Text Editor: VS Code, Vim, or Nano.
