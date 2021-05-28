# My Own System Call
I created my own system call in C, called sh_task_info(), which takes argument as PID and filename(say output.txt). It searches out task_struct() corresponding to the PID and prints out 5 fields - process name, pid, process state, RT_Priority and static priority using printk in the kernel log and save this in the filename (output.txt) supplied eariler. I also handle errors in user inputs, such as incorrect arguments, through appropriate errno and function return values 

Note: The system call was written for Linux/kernel v5.9 distribution.

## Description
I copy the user supplied file name from user space to kernel space using strncpy_from_user(). Then I traverse task_struct using for_each_process(task). If the pid matches the input pid then it prints 5 fields which are process name, pid, process state, RT_Priority and static priority using printk in the kernel log. Also I keep concatenating these values to a string called data which I will later write into the file. For writing to file I use filp_open() to open and create the file, and use kernel_write to write data to the file. I then close the file using filp_close() and return 0, on successful execution. If I encounter any errors, I’ve handled them appropriately in the program, and explained them below.

## User Input
I have hardcoded the user inputs in test.c file. The pid is passed using getpid() and the filename
supplied is “output” which is saved in the home directory.

## Expected Output
On doing dmesg on the terminal we can see the kernel log printed on the terminal. It will show
“My System Call” which means I was able to enter my system call. Then it will print the 5 fields
of the given pid, provided it exists in task_struct. The next line will tell us that the data was
saved in the given input file, which we can confirm by opening the file saved in the home
directory. If there was error, then it will be printed in the terminal.

## Errors Handled
- The pathname should not exceed length of 300. It should also not be empty.
- The file to be written to couldn’t be opened
- The pid given does not correspond to any task in task_struct

Please read the [WriteUp.pdf](WriteUp.pdf) for a more detailed description.
