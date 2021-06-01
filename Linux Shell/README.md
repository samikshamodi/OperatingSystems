# Linux Shell
A Linux shell coded in C. It supports 10 commands with 2 options each and accepts all possible arguments. It has 5 internal and 5 external commands which were implemented using fork,execvp,wait and exit system calls. It also handled various corner cases and errors.

## How My Shell Works
The shell works in an infinite loop (while(1)). It prints the shell prompt, takes the user input as string using fgets, then parses it using strtok and stores them in a 2d array called command.

Then it checks the command, if it is null then it justs print another prompt, else if it is a valid internal command then it executes that command internally, else if it is a valid external command then executes it using fork, execvp, and wait, else tells the user that it is an invalid command. It also saves the history of the current shell using a 2d char array.

## Assumptions
- Only the history of the current shell session is saved.
- It does not support two options at once for any command. For eg ls -a is valid but ls -a -r is not.
- In ls only one directory can be read at a time. ls Desktop is valid but ls Desktop Pictures is not.

## Options for Shell Commands
My shell handles following
Internal commands - cd, echo, history, pwd and exit 
external commands - ls,cat,date,rm and mkdir 

- cd
  - .. goes back one folder up
  - ~ goes to home
- echo
  - -n do not append a newline
  - -E explicitly suppress interpretation of backslash escapes
- history
  - -c clear the history list by deleting all of the entries
  - -w write the current history to the history file. If FILENAME is given, it is used as the history file
- pwd
- exit
- ls
  - -a do not ignore entries starting with .
  - -r reverse order while sorting
- date
  - -u print or set Coordinated Universal Time (UTC)
  - -I (capital i) output date in ISO 8601 format
- cat
  - -n number all output lines
  - -E display $ at end of each line
- mkdir
  - -p no error if existing, make parent directories as needed
  - -v print a message for each created directory
- rm
  - -i prompt before every removal
  - -d remove empty directories

## Handling of Shell Commands
- cd   
It uses chdir to navigate to the given directory.
  - If more than one argument is given, it prints the error message “Too many arguments.
  - If an invalid option is given, it prints the error message “Invalid argument”.
  - If the given directory does not exist, it prints the error message “Directory not found”.

- echo   
It processes the input according to the flag and gives the required output.

- history    
History is kept track of in the shell using a 2d char array. To print the history it traverses the array and prints it.
  - If just -w option is used without any file name then it writes the current history to the .txt, else it creates the file specified and writes history to that file.
  - If the program is unable to create the file, it prints the error message “Unable to create file”.
  - If an invalid option is given, it prints the error message “Invalid argument”.
  - If arguments are given with history for eg history hello world, then it prints the message “Invalid argument”.

- pwd    
It prints the current working directory by using getcwd
  - If getcwd returns null, it prints the error message “Unable to get working directory” 
  - If an invalid option is given then it print the error message “Invalid argument”

- exit   
It uses exit() to exit the current terminal session.

- ls   
I used readdir to read the files present in the given directory and store them in a 2d array a. Then depending on the flag given I sort them alphabetically. If the flag is -r then I sort them in reverse order. If the flag is -a I print the directories starting with ‘.’ also.
  - If an invalid option is given, it prints the error message “Invalid argument.”
  - If the directory given can’t be found then it prints the error message “Directory not found”
  - If multiple directories are given like ls Desktop Picture, then it shows the error message “Too many arguments”

- date    
I use the time function for this. Passing the argument local to asctime() gives me the IST time and passing the argument utc to asctime() gives me the utc time. I also use strftime() to print the date
in iso 8601 format.
  - If the function time() is unable to execute properly, it prints the error message “Time failed” and returns.
  - If an invalid option is given, it prints the error message “Invalid argument”

- cat    
I use fopen to open the file given as argument then read it using fgets and then print it based on the options.
  - If the given file doesn’t exists, it prints the error message “File [name] doesn’t exist”
  - If an invalid option is given, it prints the error message “Invalid argument”

- mkdir    
I use stat to find out whether the directory already exists, if it doesn’t I use mkdir to make the directory if the command and arguments are valid. Depending if the -v flag is used, I print the message for each directory created.
  - If just mkdir is given without any arguments, it prints the error message “Insufficient arguments”.
  - If I don’t specify the name of the directory to be made after the option eg mkdir -p , it prints the error message “Insufficient arguments”
  - If the directory to be created already exists, it prints the error message “Directory [name] already exists”
  - If mkdir is unable to create the directory, it prints the error message “Unable to create directory”
  - If a nested directory is given eg abc/xyz and abc doesn’t exist and the -p option is not used, it prints the error message “Cannot create directory [name]. No such file or directory exists”
  - If an invalid option is given, it prints the error message “Invalid argument”

- rm    
I use remove to remove the files and directory (if they’re empty and -d option is used). If the -i option is used, it asks for a yes before deleting the file, and deletes only if the answer is yes.
  - I do not allow the user to delete the files that are used by my shell to run. If they’re given as arguments, it prints the error message “You do not have permission to remove [name] file”
  - If you try to do rm on directories without -d option, it prints an error message “Can’t do rm on directories”. I use opendir() to determine if the given argument is a directory.
  - If you try to do rm on non empty directories even with the -d option, it prints an error message “Cannot remove file ordirectory”
  - If just rm is used without any argument, it prints the error message “Insufficient arguments”
  - If an invalid option is given, it prints the error message “Invalid argument” 

- If any command other than the ones specified above are used, it prints the error message “Invalid command”.


Please read the [WriteUp.pdf](WriteUp.pdf) for a more detailed description.
