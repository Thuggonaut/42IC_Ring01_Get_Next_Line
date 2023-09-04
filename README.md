# 📑 get_next_line():

This project helps us understand more about:
1. File I/O: 
	`get_next_line` involves reading from a file descriptor, which is a fundamental operation in many programs. It teaches you how to use functions like `read` to interact with file descriptors.
2. Static Variables: 
	`get_next_line`` uses static variables to keep track of the stash string between function calls. This teaches you about the lifetime and scope of static variables.
3. Error Handling: 
	`get_next_line` needs to handle several potential error conditions, such as an invalid file descriptor or a failed memory allocation. This teaches you about error handling and how to write robust code that can handle unexpected situations.
4. Buffering: 
	The concept of a "storage" string in get_next_line is a form of buffering. It teaches you how buffering can improve the efficiency of I/O operations by reducing the number of system calls.
5. Multi-file Descriptor Management: 
	The bonus part of `get_next_line` involves managing multiple file descriptors. This teaches you how to write code that can handle multiple inputs or outputs, which is a common requirement in many programs.


## 🔵 Preface:
- This project is the most challenging in Ring01 imo, but as usual, I learn best by drafting a plan, tackling new concepts, and write too many notes (if you read them, you will probably need eye drops).
- I give credit to Nikito, who's video helped me understand how the function works. [Watch his video here](https://www.youtube.com/watch?v=-Mt2FdJjVno&t=164s)
- We will be completing both the [Mandatory](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-the-mandatory-part) and [Bonus](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-the-bonus-part) parts. Here is the outline:
	- Step 1: [Write the structure of directories and files required](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-structure-of-directories-and-files)
	- Step 2: [Learn Static Variables](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-step-2-learn-static-variables)
	- Step 3: [Learn File descriptors and File I/O functions](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-learn-file-descriptors-and-file-io-functions)
	- Step 4: [Learn Dynamic memory allocation functions](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-step-4-learn-dynamic-memory-allocation-functions)
	- Step 5: [Learn the `-D BUFFER_SIZE` flag](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-step-5-learn-the--d-buffer_size-flag)
	- Step 6: [Understand get_next_line](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-step-6-understand-get_next_line)
	- Step 7: [Code get_next_line](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-step-7-code-get_next_line)
	- Step 8: [Test our get_next_line](https://github.com/Thuggonaut/42IC_Ring01_Get_Next_Line/blob/main/README.md#-step-8-test-get_next_line)


## 🔵 The Mandatory part:

Create a function called `get_next_line()` that takes in a file descriptor to read from, and returns a line read from the file descriptor. 


### 🔹 Note:
1. Repeated calls (e.g., using a loop) to your `get_next_line()` should let you read the text file pointed to by the file descriptor, one line at a time. 
2. `get_next_line()` should return the line that was read, otherwise `NULL` if there is nothing else to read, or an error occured. 
    - The returned line should include the terminating `\n` character, except if the end of the file was reached and does not end with a `\n`.
      - Try to read as little as possible each time `get_next_line()` is called (don't read the whole file and then process each line). 
      - If you encounter a new line `\n`, you have to return the current line.
3. `get_next_line()` should work both when reading a file, and when reading from the standard input.
4. The header file `get_next_line.h` must contain the prototype of `get_next_line()`.
5. Add all needed helper functions in the `get_next_line_utils.c` file.
6. Because you will need to read files in `get_next_line()`, add this option to your compiler call: `-D BUFFER_SIZE=n`
    - It will define the buffer size for `read()`.
    - The buffer size value will be modified by Moulinette to test your code.
    - This project must be able to compile with and without the `-D BUFFER_SIZE` flag in addition to the usual flags. You can choose the default value of your choice.
7. Compile your code as follows (e.g. with a buffer size of 42):
   `cc -Wall -Wextra -Werror -D Buffer_size=42 <files>.c`
8. `get_next_line()` will be considered as having an undefined behaviour if the file pointed to by the file descriptor changed since the last call whereas `read()` didn't reach the end of the file.
9. `get_next_line()` will also be considered as having an undefined behaviour when reading a binary file.
    - however, you may choose to implement a logical way to handle this behaviour.
10. Consider, whether your function will work if the `BUFFER_SIZE` value is `9999`, `1`, or `10000000`, and why it is so.


### 🔹 Forbidden:
- Your libft library
- `lseek()`
- Global variables


### 🔹 Prototype:
`char  *get_next_line(int fd);`


## 🔵 The Bonus part:

1. Develop `get_next_line()` using only one static variable.
2. Your function can manage multiple file descriptors at the same time. For example:
   - If you can read from the file descriptors 3, 4 and 5, you should be able to read from a different fd per call without losing the reading thread of each file descriptor or returning a line from another fd.
   - This means, you should be able to call `get_next_line()` to read from fd 3, then fd 4, then fd 5, then once again 3, 4, and so forth.
3. Append the `_bonus.[c\h]` suffix to the bonus part files.
   - In addition to the mandatory part files, you will turn in the 3 following files:
       - `get_next_line_bonus.c`
       - `get_next_line_utils_bonus.c`
       - `get_next_line_bonus.h`


## 🔵 Step 1: Structure of directories and files
```
get_next_line/
│
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── get_next_line_bonus.c
├── get_next_line_utils_bonus.c
└── get_next_line_bonus.h
```

## 🔵 Step 2: Learn Static Variables

1. 🔹 **A static variable in C:**
	- is a special in that it retains its value across multiple function calls and persists throughout the entire execution of the program.
	- In the case of our `get_next_line.c`, a static variable (e.g. `string`) retains its value between function calls. 
		- Without `static`, `string` would be reinitialised to its default value every time `get_next_line()` is called (for example, in a loop).
		- With `static`, once `string` is initialised, it keeps its value until the program ends. This is important for the function to remember the `string` between calls. For example, it needs to remember the remainder of a line after a `\n` is found. When the function is called again, it's able to pick up where it left off. This will make more sense later. 

2. 🔹 **Syntax:**
	- `static data_type variable_name = initial_value;`
	
3. 🔹 **Properties of static variables in C:**
	- Lifetime: 
		- The lifetime of a static variable extends throughout the entire execution of the program.
	- Scope: 
		- A static variable can have either global or local scope. 
		- If declared inside a function, it has local scope, and if declared outside of any function, it becomes a global variable. See #5 & #6
	- Memory Allocation: 
		- A static variable’s memory is allocated in the data segment of the program’s memory, rather than the stack. See #7
	- Initialization: 
		- A static variable is initialized only once during program execution, at the time of program loading.
	- Thread Safety: 
		- Static variables are not thread-safe by default. 
			- <sub> A thread in programming is a small set of instructions that are scheduled and executed independently by the Central Processing Unit (CPU) of a computer.</sub> 
			- <sub> All threads of a process share the same address space, and since a static variable has a fixed address, its state is shared by all the threads.</sub>
			- <sub> If multiple threads access the same static variable simultaneously, it can lead to race conditions and unexpected behavior.</sub>
				- <sub> A race condition arises when the outcome of a program depends on the indeterministic ordering of operations in different threads.</sub>
			- <sub> In the context of `get_next_line`, it reads from a file descriptor and stores interim results in a static variable, which retains its value across multiple calls to the function. However, if you have multiple threads in your program and they're all calling get_next_line concurrently, they could all attempt to access and modify this static variable simultaneously, which could lead to inconsistent results or errors. This concept is referred to as thread safety.</sub>

4. 🔹 **Example of a Static Variable in C:**
	```
	#include <stdio.h>

	void countFunctionCalls() 
	{
    	static int count = 0;
    	count++;
    	printf("This function has been called %d times\n", count);
	}

	int main() 
	{
    	countFunctionCalls();
    	countFunctionCalls();
    	countFunctionCalls();
    	return (0);
	}
	```

	- In this example, the `count` variable is declared as a `static integer` inside the `countFunctionCalls` function. 
		- Each time the function is called, `count` is incremented by one and its updated value is printed to the console. 
		- Because `count` is a static variable, it retains its value between function calls, allowing it to track the total number of times `countFunctionCalls` is called during the program's execution.

5. 🔹 **Difference Between Static Global and Static Local Variables:**
	- A static global variable is declared outside the main function and can be used anywhere inside the program, whereas
	- A static local variable is declared inside a function or a block and can only be used within the scope in which it is declared.
	- A static global variable is not accessible outside the program. 
	- Example of both a static global variable and a static local variable:
	```
	#include <stdio.h>

	static int global_static_var = 10;  // global static variable

	void func() 
	{
    	static int local_static_var = 20;  // local static variable
    	printf("%d\n", local_static_var);
    	printf("%d\n", global_static_var);
	}

	int main() 
	{
    	func();
    	printf("%d\n", global_static_var);
    	printf("%d\n", local_static_var);  // This would cause a compile error
    	return (0);
	}
	```
 
	- In the above example, `global_static_var` can be accessed by any function in the file, while `local_static_var` can only be accessed within the func function.
	- Both local and global static variables have static storage duration, meaning they exist for the entire lifetime of the program. They are created and initialized only once and keep their value between function calls or blocks.

 6. 🔹 **Visibility:**
	- The visibility of a variable refers to the parts of the code from which a variable can be accessed or referred to.
	- A local static variable is only visible within the function or block where it is declared.
	- A global static variable is visible to all functions in the file where it is declared, but it is not visible to other files. 
	- This is due to the internal linkage provided by the static keyword at file scope. 
	- This means that the global static variable is "private" to the source file and cannot be accessed directly from other source files.

	```
	// file1.c
	#include <stdio.h>

	static int global_static_var = 10;  // global static variable

	void func1() 
	{
    	printf("%d\n", global_static_var);
	}

	// file2.c
	#include <stdio.h>

	extern int global_static_var;  // This would cause a linker error

	void func2() 
	{
    	printf("%d\n", global_static_var);
	}

	int main() 
	{
    	func1();
    	func2();
    	return (0);
	}
	```

	- In the above example, the `global_static_var` is a `global static` variable declared in `file1.c`. 
	- It can be accessed by the `func1` function in the same file, but cannot be accessed by the `func2` function in `file2.c`.

7. 🔹 **In summary**
	- Static variables in C are an important feature that allow for the creation of variables that persist throughout the program’s execution, reducing the need for recomputing values and optimizing performance. 
	- However, it's important to be aware of potential issues that can arise when using static variables in a multi-threaded environment or when accessing them outside of their defined scope.


## 🔵 Step 3: Learn File descriptors and File I/O functions
- `open()`
- `read()`
- `close()`
- These functions will help you read from the file descriptor provided.

1. File Descriptors are a key concept in Unix and Unix-like operating systems. 
	- They are used to manage input and output operations in C programming. 
	- A file descriptor is an integer that uniquely identifies an open file in an operating system.
	- Standard input `STDIN`, standard output `STDOUT`, and standard error `STDERR` are the first three file descriptors that are used by default on an operating system that is similar to Unix. 
	- When any process begins, the file descriptors table for that process opens automatically with its `fd`  `0`, `1`, and `2` entries. Each of these three `fd` references an item in the `file table` for a file called `/dev/tty`.
	- C programming provides a number of in-built functions to support reading from and writing to files. 
	- The open(), read(), write() and close() used to perform input/output system calls are located in the `unistd.h` library.

2. `open()`:
	- Is used to open a file for reading, writing, or both. 
	- This function can also create a file if it doesn't already exist. 
	- The flags that are passed as arguments are defined inside the `fcntl.h` header file.
	- prototype: 
		`int open(const char *pathname, int flags);`

3. `read()`:
	- Reads a specified number of bytes (indicated by `cnt`) from a file (indicated by the file descriptor `fd`) into a memory area (indicated by `buf`). 
	- Prototype: 
		`ssize_t read(int fd, void *buf, size_t cnt);`
		- Here, `fd` is the file descriptor from which to read, `buf` is the buffer into which to read, and `cnt` is the number of bytes to read.
	- `read()` returns a `ssize_t` which is an integer. 
		- So, we send `read()` a file descriptor, which is an integer.
		- We send it a pointer of type `void` which is a buffer.
		- We send it a second `size_t` which is a number of bytes. 
		- Then, `read()` will read from a file, then store what it read in a variable. 
		- On objects capable of seeking, the `read()` starts at a position given by the file pointer associated with `fd`.
		- Upon return from `read()`, the file pointer is incremented by the number of bytes actually read. 
		- So, when you call it for the first time on a file, the file pointer will be positioned right before the first character of that file. 
		- Then, you tell it to “read n bytes”, and say, `n = 5`, it’ll read 5 bytes of characters, while advancing the file pointer five bytes forward. 
		- Then, you tell it to “store the 5 characters read in the buffer I’ve sent you”, and it’ll store them in the buffer. 
		- Finally, it returns the number of bytes it successfully read. 
		- Calling `read()` again on the same file that was just read, it’ll remember the position of the file pointer which will be where it last read from, as it’s associated with the file descriptor. 
			- So, the file pointer stays where it last was, at the end of the first call, and upon calling it again it’ll know what it’s already read. 
			- We tell it to read 5 bytes again, and it’ll read 5 bytes then increment the file pointer 5 bytes forward again. Then it’ll store 5 bytes of characters read in the buffer, and return `5` to indicate it’s successfully read 5 bytes. 
		- Calling `read()` in a loop on the same file will always overwrite the buffer with the new characters read, as it uses the same memory. 
		- What happens when we call `read()` again but there are less bytes than `n` to read before the end of a file?
			- It’ll read the remaining bytes, then stores the read characters in the buffer, then returns the number of bytes it’s read, and when it’s finished reading the file, it returns `0`. 
			- If we call `read()` again on the file, it’ll return us `0` because it will have succeeded in reading `0` bytes as it’s at the end of the file. 
			- If there are errors, it’ll return `1`. 

4. `close()`:
	- Tells the operating system that you are done with a file descriptor and closes the file pointed to by the file descriptor. 
	- This function is defined in the `unistd.h` header file.
	- Prototype: `int close(int fd);`


## 🔵 Step 4: Learn Dynamic memory allocation functions
- `malloc()`
- `free()`
- These functions will help you manage memory for the lines read from the file descriptor. 

1. `malloc()`: 
	- This function is used to allocate a block of memory dynamically. 
	- When using `malloc()`, you will need to specify the amount of memory you want to allocate in bytes. For example:
	```
	int *ptr = (int *)malloc(10 * sizeof(int));  // Allocate memory for 10 integers
	```
2. `free()`: 
	- This function is used when you have finished with a dynamically allocated block of memory. 
	- By passing the pointer to this block to `free()`, you can return this memory to the system so it can be reused later. For example:
	```
	free(ptr);
  	ptr = NULL;  // It is good practice to set your pointer to NULL after freeing it
	```

3. In our `get_next_line` function, we'll need to be sure to free any memory we allocate once we're done using it. 
	- This will likely be at the end of the function, once we've read and returned a line. 
	- Not doing so can result in memory leaks, where parts of memory can't be used again until the program ends, which can eventually cause the program to run out of memory and crash.


## 🔵 Step 5: Learn the `-D BUFFER_SIZE` flag

1. 🔹 **The -D flag in C:**
	- is used to define a macro that can be used within the code. 
	- It's used in the command line while compiling the code. 
	- The syntax is `-D name`, where `name` is the name of the macro to be defined. 
	- This can be followed by `=` and the value to assign to the macro, if any.
	
2. 🔹 **BUFFER_SIZE** 
	- For example, in our case `-D BUFFER_SIZE=42` would define a macro named `BUFFER_SIZE` with a value of `42`. This macro can then be used in our code as if it were a constant.
	- In our `get_next_line`, we define a `BUFFER_SIZE` to read chunks of a file in the function. 
	- The `BUFFER_SIZE` is used in the `read()` function, which reads at most `BUFFER_SIZE` number of bytes from the file into the buffer:
		```
		ssize_t read(int fd, void *buf, size_t cnt);
		```

    - Recall, `fd` is a file descriptor pointing to the file to be read. `buf` is a buffer where the read content will be stored, and `cnt` is the number of bytes to read from the file.
	- You can change the buffer size at compilation. When you compile the C source code, the -D option will set a preprocessor macro. 
    - Compile your code like this, e.g. with buffer size of 42:

        `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c`

    - Then, the `BUFFER_SIZE` macro is given the value '42', and it can be used in your program. 
            - A `BUFFER_SIZE` of `1` means that you're reading in a file `1` byte at a time, which is very inefficient but can be useful for 
              testing your program. 
            - A `BUFFER_SIZE` of `10000000` means you're reading in the file `10000000` bytes at a time, which might be faster but 
              will use a lot more memory.

	- When we compile our program with `-D BUFFER_SIZE=42`, this would mean that `read()` will read in chunks of `42` bytes at a time from the file, until it reaches the end of the file. 

3. 🔹 **Defining the default in the `get_next_line.h` file**
	- In case the "-D BUFFER_SIZE flag" is omitted during compiling (as instructed in the .pdf), we need to define a default buffer size within our header file. 


## 🔵 Step 6: Understand get_next_line

1. 🔹 Recall, file descriptors “fd” is a reference to a file that is opened on your computer. 
	- We tell `get_next_line()` to go look in this file, and return us a string of characters, which will be the line that was read from the file.

2. 🔹 The first time we call `get_next_line()`, it’ll retrieve the first line of the file.
	- Thereafter, we should be able to read the entire file by calling `get_next_line()` in a loop on the file. 
		- In a loop, after returning the first line of a file `line 1`, whenever `get_next_line()` is called again on the file, it will send the function the next line `line 2`, then `line 3`, and so on, until there are no more lines to read from in the file. 

3. 🔹 The return value of `get_next_line()`, is the line that was read from a file, if successful. 
	- If not successful, i.e. there are no more lines to read, or there is an error during execution, it’ll return `NULL`. 

4. 🔹 Recall, the size of the buffer will be defined at compilation, so it’ll vary, and it will be dependent on the user telling `read()` how many bytes of the file they want to read.
	- `cc -Wall -Wextra -Werror -D Buffer_size=42 <files>.c`

5. 🔹 Recall, calling `read()` in a loop on a file will overwrite the same buffer each time it stores the new bytes of characters read. 
	- We need a solution for this, e.g. we create a `static variable` called `stash` so that the previously read bytes are stored in here, and not lost/overwritten. 
	
6. 🔹 We need `get_next_line()` to retrieve a line that ends with a `\n`.
	- This means, we will need to check in our `stash` (what's been read) if a `\n` has been encountered. 
		- If no `\n` has been found, we will continue to call `read()`. 
			- Then it’ll read the next `n` bytes of characters
			- Then increment the pointer `n` bytes forward
			- Then store in the buffer the `n` bytes read
			- Then if successful, return the number of bytes read. 
	- Then store the characters read into `stash`. 
	- We look inside `stash` again to check if there is a `\n` in there. 
		- If no `\n` has been reached, then we continue our work again and call `read()`. 
		- If in our `stash` we did find a `\n`
			- This means we have a line break in our file.
			- We then want to extract this line (a string of characters), from our reserve `stash`.
	- In order to send this extracted line to `get_next_line()` for it to return to us, we will need a variable e.g. called “line”. 
		- Our variable `line` will store the extracted characters we want, including the line break `\n`, or the `\0` signalling the end of the file. 
	- Now that `get_next_line()` has returned us our first line of the file, we will need to clean up our `stash`, as what it had previously stored was already returned, and we no longer need `stash` to store it. 

7. 🔹 Recall, when `read()` is called subsequently, the file pointer to the buffer remains where it last completed its `n` bytes read, because it is associated with the file descriptor of that file.
	- This means, after our first line that was read and returned, even though we’d already cleaned up our `stash`, when we come back and call `get_next_line()` again, the `stash` variable is re-initialized, back to where the file pointer was last left off. 


## 🔵 Step 7: Code get_next_line
Now that we understand how `get_next_line()` should function, we will need to have the following considerations:

1. 🔹 We need a helper function that first reads `BUFFER_SIZE` bytes from the `fd` and store it in a buffer `line_read`.
	- We will call it `read_from_fd()`.
	- Make it return the line that's read.
	

2. 🔹 We need a helper function to look inside `stash`, and search for either the `\n` or the `\0` (signalling the end of `stash`).
	- We will call it `process_line()`.
	- Make it return the extracted `line` up to the `\n`.
	- In order for `process_line()` to: 
		- 1. extract one portion of `stash`, and 
		- 2. update `stash` to contain the "leftover" characters from the other portion, thereby "splitting" `stash` at the `\n`, new memory needs to be allocated. 
	- Recall, from our libft library, `ft_substr()` allocates memory, and copies into a new string, the characters from a starting index of the input string, to an ending index. 
	- We can use pointer arithmetic to calculate the positions of the start and end indices for the portions of `stash` we need copied. 

3. Finally, we have our main function `get_next_line()`.
	- We make it put the `line_read` inside `stash` so we can later go inside `stash` and search for the `\n`.
	- At some point, we will have:
		- a complete line up to the `\n` to extract
		- after which we will have an updated `stash` containing the `leftovers`
		- if there is more data to read, then we will have a new `line_read`
	- If there is a new `line_read`, this means we will need to append this to the `stash` for the next search of the `\n`. 
	- We will need a helper function to append the new `line_read` to the `stash`.
		- Recall, from our libft library, `ft_strjoin()` creates a new string by allocating memory enough to hold two strings, and concatenates them.
	- We want to keep calling `get_next_line()` until all the lines are returned, and there is no more lines to read from the `fd`.


7. 🔹 Let's write some pseudo code to see how this might all come together:
	```
	//Call `get_next_line()` with a file descriptor
		//Declare a static variable `stash` to hold the leftovers after a line is extracted
		//Declare a variable to store the current data that was read
		//Declare a variable to store the extracted line in which our function returns
	
	//Check for file descriptor, BUFFER_SIZE, and read() errors

	//Account for the first call of the function, where `stash` will be empty
		//Initialise it to an empty string, preparing for an accumulation of characters next read

	//If there is a complete line processed, extract it
		//Return the line

	//If there is more data to read
		//Append the new data to the stash
		//Call `get_next_line()` again. Possibly use recursion
	
	//If there is no more data to read
		//Return the leftovers from the stash
		//Calling `get_next_line()` again will return NULL and our work is done
	```


## 🔵 Step 8: Test get_next_line

1. 🔹 Write a main():
	- Ensure all the headers are included, e.g. `<fcntl.h>` for file descriptor and IO operations; and `<stdio.h>` to call `printf()`.
	- Call `open()` to open a text file, e.g. `open("test.txt", 0_RDONLY);`
	- Use a `while loop` to call our `get_next_line()`, where `read()` is called
	- Print the results (the lines returned)
	- Call `close()` to close the file after it's done its job

2. 🔹 Write some test .txt files
	- Ensure these files are in the same directory as our `get_next_line()` source files.

3. 🔹 Compile using `cc -Wall -Wextra -Werror -D Buffer_size=5 <files>.c`
	- Test with a small number of BUFFER_SIZE. 
	- Test without the -D flag.
	- Test with francinette.


## 😎 All the best, friends! 
