# Execution_Time-C

This C program is used to measure the execution time of another program. It does so by using the clock() function from the time.h library to measure the time before and after the execution of the program. The time difference between the start and finish times is calculated and stored in the working_time variable.

The program takes two command line arguments: the first argument is the name of the program to be executed, and the second argument is a string that specifies whether the execution time should be measured in seconds ("s") or clock ticks ("t").

The program first checks that the correct number of arguments have been provided (exactly two). If the correct number of arguments have not been provided, an error message is printed and the program exits.

The program then attempts to open the file specified by the first command line argument in read mode. If the file cannot be opened, an error message is printed and the program exits.

Next, the program creates a child process using the fork() function. The child process executes the program specified by the first command line argument using the execl() function, while the parent process waits for the child process to finish using the waitpid() function.

After the child process has finished executing, the clock() function is called again to get the current time, and the difference between the start time and the finish time is calculated. The execution time is then printed to the console in either seconds or clock ticks, depending on the value of the second command line argument.

Finally, the program attempts to open a file called "results.txt" in the user's home directory in append mode. If the file cannot be opened, an error message is printed and the program exits. The execution time is then written to the file, along with the name of the program that was executed. The file is then closed.
