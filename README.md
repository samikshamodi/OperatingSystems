# Operating Systems
These are some of the assignments I did in my 4th semester at IIITD for the course CSE231: Operating Systems taught by Dr. Sambuddho Chakravarty.

- Bootlader in asm 
  - Implemented a simple bootloader, booted via a legacy BIOS and booted using qemu emulator

- Combining C and Assembly
  - Combined a C program with an assembly language (x86-64) function using gcc and nasm

- Linux Shell 
  - Implemented a linux shell in C. It supports 5 internal and 5 external commands with 2 options each and handles various corner cases and errors

- Modifying CFS Scheduler 
  - Added a soft real-time requirement to a process and modified the cfs scheduler such that higher priority is given to a processes soft real-time requirement as compared to the vruntime that is normally considered

- My Own System Call
  - Implemented my own system call called sh_task_info() which prints out all the fields corresponding to a given PID and saves it in a file given by the user

- Semaphores
  - Implemented my own blocking and non-blocking counting sempahore with primitives wait() and signal() using pthread library
  - Then used the above semaphore to solve a modified version of the dining philosphers' problem

