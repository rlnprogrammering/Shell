	
		--- How the shell program (CLI) works ---

This shell program is capable of taking linux commands entered by the user, 
and executing said commands to perform the action of the specified commands.

The user runs the program and now has access to our custom shell program. 
Here it’s possible for the user to input a command (or more) to be executed by the program.

Once a command has been entered, the program creates a child process which 
handles the execution of the command. 
Once the command has been executed, the parent will terminate the child 
and the program waits for the next input from the user.

If multiple commands have been entered in a “pipe” format (ex. “Command 1 | Commands 2”),
the shell program will create a child process which executes the first command.
Once the command is executed, another child process will be created 
and the output from the previous child process will be used as an input for the next child process.
Once all commands in the pipe have been executed, the parent process will terminate all the children 
and wait for the next input from the user.

		--- How to use the shell program ---

	1. To run the program, save the shell.c and shell.h files in a directory.

	2. Go to the directory in your linux terminal by using the “cd” command 
	   and then typing in the filepath for the folder.

	3. Before we’re able to execute the program, first compile the program by typing 
	   “gcc shell.c” or “gcc shell.c -o shell” to specify an appropriate name for the executable.
	 
	4.The program can now be run by typing in “./a.out” or “./shell”,

		--- Concepts used in the shell program ---

---System Call:

A system call is when a program sends a request to the kernel, 
this is usually done by the program, interfacing with the kernel behind the scenes. 
System calls work the same way as function calls, they respond to arguments and return values. 
However, during a system call the program switches from user space to a kernel space,
which changes its level of access to the systems. This is achieved by using a unique trap function.

---I/O redirection: 

As the name implies I/O (Input / Output) redirection does exactly that, 
it changes the way the from where the user specific commands reads the input, 
and sends the output. When working with bash shell it has 3 commonly used streams in I/O redirection, 
standard input (stdin), standard output (stdout) and standard error (stderr). Stdin takes input from the keyboard, 
stdout sends the output to the display, and stderr also sends error messages to the display.

To manually redirect the streams in UNIX the user can use special characters to implement a redirection command.
 For example, if the user wanted to redirect the stream into a file, they could use brackets  to do so. 
For stdin it would be“<”, stdout “>”, and “2>” for stderr. Furthermore, 
if the user doesn't want to overwrite anything using the redirection commands, 
they could opt to use double brackets instead “>>”.

On the other hand if the user wishes to redirect the output stream of one program to another, 
they would use the pipe function instead, which is performed by using this “|” character. 
When the pipe function is called it sends the standard output of one program to the other, 
be mindful that only the second program's output will be shown in the terminal.

---Program environment: 

The UNIX environment is defined by the environmental variables. 
These variables are defined by the system, the user and by the shell script. 
Simply put, the variables are characters which have been assigned different values. 
These values can be any type of data; such as numbers, files, or user specific commands.
 As the user you can use the dollar sign “$” character to customly set these variables.


		---Background program execution---

When using the linux terminal, the user can type in commands that will get executed as a foreground process.
 If the user wishes to execute a command as a background process, it’s possible to add an ampersand (“&”) 
to the end of the command to execute it in the background. This allows the user to run other processes 
without having to wait for the first process to execute.
