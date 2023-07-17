Mandatory part:

Create a function called get_next_line() that takes in a file descriptor to read from, and returns a line read from the file descriptor. 

Note:
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

Forbidden:
- Your libft library
- `lseek()`
- Global variables


Prototype:
`char  *get_next_line(int fd);`


Bonus part:

1. Develop `get_next_line()` using only one static variable.
2. Your function can manage multiple file descriptors at the same time. For example:
   - If you can read from the file descriptors 3, 4 and 5, you should be able to read from a different fd per call without losing the reading thread of each file descriptor or returning a line from another fd.
   - This means, you should be able to call `get_next_line()` to read from fd 3, then fd 4, then fd 5, then once again 3, 4, and so forth.
3. Append the `_bonus.[c\h]` suffix to the bonus part files.
   - In addition to the mandatory part files, you will turn in the 3 following files:
       - `get_next_line_bonus.c`
       - `get_next_line_utils_bonus.c`
       - `get_next_line_bonus.h`


Structure of directories/files:
get_next_line/
  - get_next_line.c
  - get_next_line_utils.c
  - get_next_line.h
  - get_next_line_bonus.c
  - get_next_line_utils_bonus.c
  - get_next_line_bonus.h


Learn:
1. Static Variables
2. File descriptors and File I/O functions:
    - `open()`
    - `read()`
    - `close()`
    - These functions will help you read from the file descriptor provided.
4. String manipulation functions:
    - `strchr()`
    - `strlen()`
    - `strncpy()`
    - `strdup()`
    - These functions manipulate the strings read from the file descriptor and return the lines as required.
5. Dynamic memory allocation:
    - `malloc()`
    - `realloc()` 
    - `free()`
    - These functions will help you manage memory for the lines read from the file descriptor. 
6. The `-D BUFFER_SIZE` flag


Nikito: https://www.youtube.com/watch?v=-Mt2FdJjVno&t=164s

Recall, file descriptors “fd” is a reference to a file that is open on your computer. 

We tell `get_next_line()` to go look in this file, and return is a string of characters, which will be the line that was read from the file.

The first time you call `get_next_line()`, it’ll retrieve the `first line` of the file, and then you should be able to read the entire file calling `get_next_line()` in a loop on the file. In a loop, after returning the first line of a file `line 1`, each time `get_next_line()` is called again on the file, it will send the function the next line `line 2`, then `line 3`, and so on, until there are no more lines to read from in the file. 

The return value of `get_next_line()` then, is the line that was read from a file, if successful. If not successful, I.e. there are no more lines to read, or there is an error during execution, it’ll return `NULL`. 

/*
1. STATIC VARIABLES:

	a.	a. A static variable in C is a special type of variable that retains its value across multiple function calls and persists throughout the entire execution of the program. 
	⁃	- This is in contrast to automatic variables, which lose their value once the function they are declared in completes execution.
	b.	Syntax:
	⁃	`static data_type variable_name = initial_value;`
	c.	Properties of static variables in C:
	⁃	Lifetime: 
	⁃	The lifetime of a static variable extends throughout the entire execution of the program.
	⁃	Scope: 
	⁃	A static variable can have either global or local scope. 
	⁃	If declared inside a function, it has local scope, and if declared outside of any function, it becomes a global variable. See # .f & .g
	⁃	Memory Allocation: 
	⁃	A static variable’s memory is allocated in the data segment of the program’s memory, rather than the stack. See # .h
	⁃	Initialization: 
	⁃	A static variable is initialized only once during program execution, at the time of program loading.
	⁃	Thread Safety: 
	⁃	Static variables are not thread-safe by default. 
	⁃	All threads of a process share the same address space, and since a static variable has a fixed address, its state is shared by all the threads.
	⁃	If multiple threads access the same static variable simultaneously, it can lead to race conditions and unexpected behavior. 
	⁃	A race condition arises when the outcome of a program depends on the indeterministic ordering of operations in different threads.
	d.	Example of a Static Variable in C:
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

	⁃	In this example, the `count` variable is declared as a `static integer` inside the `countFunctionCalls` function. 
	⁃	Each time the function is called, `count` is incremented by one and its updated value is printed to the console. 
	⁃	Because `count` is a static variable, it retains its value between function calls, allowing it to track the total number of times `countFunctionCalls` is called during the program's execution.

	e.	Difference Between Static Global and Static Local Variables:
	⁃	A static global variable is declared outside the main function and can be used anywhere inside the program, whereas a static local variable is declared inside a function or a block and can only be used within the scope in which it is declared.
	⁃	A static global variable is not accessible outside the program. 
	f.	Example of both a static global variable and a static local variable:
 
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
    // printf("%d\n", local_static_var);  // This would cause a compile error
    return 0;
}

	⁃	In the above example, `global_static_var` can be accessed by any function in the file, while `local_static_var` can only be accessed within the func function.
	⁃	Both local and global static variables have static storage duration, meaning they exist for the entire lifetime of the program. They are created and initialized only once and keep their value between function calls or blocks.

	g.	Visibility:
	⁃	The visibility of a variable refers to the parts of the code from which a variable can be accessed or referred to.
	⁃	A local static variable is only visible within the function or block where it is declared.
	⁃	A global static variable is visible to all functions in the file where it is declared, but it is not visible to other files. 
	⁃	This is due to the internal linkage provided by the static keyword at file scope. 
	⁃	This means that the global static variable is "private" to the source file and cannot be accessed directly from other source files.

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
    return 0;
}
```

	⁃	In the above example, the `global_static_var` is a `global static` variable declared in file1.c. 
	⁃	It can be accessed by the `func1` function in the same file, but cannot be accessed by the `func2` function in `file2.c`.

	h.	A static variable’s memory is allocated in the data segment of the program’s memory, rather than the stack.
	⁃	Memory allocation for static variables is done at the time of program startup, and they live until the program ends. 
	⁃	They cannot be "freed" or "reallocation”.
	⁃	Static variables are stored in the `.BSS (Block Started by Symbol) segment` for non-initialized static variables and `.DATA segment` for initialized static variables. The actual storage location of the data will be implementation dependent.

For instance, the following code examples illustrate how static variables are allocated in memory:


```
int main(int argc, char * argv[])
{
    return 0;
}

> gcc test.c
> size a.out
text     data     bss   dec    hex   filename
1056     252      8     1316   524   a.out
```


When we declare a static variable `i` inside the main function:

```
int main(int argc, char * argv[])
{
    static int i;
    return 0;
}

> gcc test.c
> size a.out
text       data     bss   dec     hex   filename
1056     252      12    1316   524   a.out
```


And when we initialize the static variable `i` with a value:

```
int main(int argc, char * argv[])
{
    static int i = 2;
    return 0;
}

> gcc test.c
> size a.out
text     data     bss   dec    hex   filename
1056     256      8     1316   524   a.out
```

	⁃	From the above examples, we can see that the size of the `.bss` segment increased when we declared a non-initialized static variable and the size of the `.data segment` increased when we declared an initialized static variable.
	⁃	The static memory allocation is applied to global variables, file scope variables, and those variables that are declared as static. 
	⁃	In static memory allocation, memory is allocated at compile time and cannot be changed after allocation.
	⁃	One feature of static memory allocation is that the allocated variables are permanent; hence the memory in this type of allocation cannot be reused and is, therefore, less efficient. 
	⁃	This allocation uses the stack for implementing the allocation process.
	⁃	It's important to note that static variables are not stored on the heap. 
	⁃	They are stored in the BSS segment if they are uninitialized and in the data segment if they are initialized.

	i.	In summary, static variables in C are an important feature that allow for the creation of variables that persist throughout the program’s execution, reducing the need for recomputing values and optimizing performance. However, it's important to be aware of potential issues that can arise when using static variables in a multi-threaded environment or when accessing them outside of their defined scope.


2. FILE DESCRIPTORS & FILE I/O FUNCTIONS:

	a.	File Descriptors are a key concept in Unix and Unix-like operating systems. 
	⁃	They are used to manage input and output operations in C programming. 
	⁃	A file descriptor is an integer that uniquely identifies an open file in an operating system.
	⁃	Standard input `stdin`, standard output `stdout`, and standard error `stderr` are the first three file descriptors that are used by default on an operating system that is similar to Unix. 
	⁃	When any process begins, the file descriptors table for that process opens automatically with its `fd`  `0`, `1`, and `2` entries. Each of these three `fd` references an item in the `file table` for a file called `/dev/tty`.
	⁃	C programming provides a number of in-built functions to support reading from and writing to files. 
	⁃	The open(), read(), write() and close() used to perform input/output system calls are located in the `unistd.h` library.
	b.	`open()`:
	⁃	 Is used to open a file for reading, writing, or both. 
	⁃	This function can also create a file if it does not already exist. 
	⁃	The flags that are passed as arguments are defined inside the `fcntl.h` header file.
	⁃	prototype: `int open(const char *pathname, int flags);`
	c.	 `read()`:
	⁃	Reads a specified number of bytes (indicated by `cnt`) from a file (indicated by the file descriptor `fd`) into a memory area (indicated by `buf`). 
	⁃	A successful read() updates the access time for the file.
	⁃	Prototype: `ssize_t read(int fd, void *buf, size_t cnt);`
	⁃	Here, `fd` is the file descriptor from which to read, `buf` is the buffer into which to read, and `cnt` is the number of bytes to read.
	⁃	`read()` returns a `ssize_t` which is an integer. 
	⁃	We send it a file descriptor, which is an integer.
	⁃	We send it a pointer of type `void` which is a buffer.
	⁃	We send it a second `size_t` which is a number of bytes. 
	⁃	So, `read()` will read from a file, then store what it read in a variable. 
	⁃	On objects capable of seeking, the `read()` starts at a position given by the pointer associated with `fd`.
	⁃	Upon return from `read()`, the pointer is incremented by the number of bytes actually read. 
	⁃	So, when you call it for the first time on a file, the pointer will be positioned right before the first character of that file. 
	⁃	Then, you tell it to “read n bytes”, and say, `n = 5`, and it’ll read 5 bytes of characters, while advancing the pointer five bytes forward. 
	⁃	Then, you tell it to “store the 5 characters read in the buffer I’ve sent you”, and it’ll store them in the buffer. 
	⁃	Finally, it returns the number of bytes it successfully read. 
	⁃	Calling `read()` again on the same file that was just read, it’ll remember the position of the pointer which will be where it last read from, as it’s associated with the file descriptor. 
	⁃	So, the pointer stays where it last was, at the end of the first call, and up calling it again it’ll know what it’s already read. 
	⁃	We tell it to read 5 bytes again, and it’ll read 5 bytes then increment the pointer 5 bytes forward again. Then it’ll store 5 bytes of characters read in the buffer, and return `5` to indicate it’s successfully read 5 bytes. 
	⁃	Calling `read()` in a loop on the same file will always overwrite the buffer with the new characters read, as it uses the same memory. 
	⁃	What happens when we call `read()` again but there are less bytes than `n` to read before the end of a file?
	⁃	It’ll read the remaining bytes, then stores the read characters in the buffer, then returns the number of bytes it’s read, and when it’s finished reading the file, it returns `0`. 
	⁃	If we call `read()` again on the file, it’ll return us `0` because it will have succeeded in reading `0` bytes as it’s at the end of the file. 
	⁃	If there are errors, it’ll return `1`. 
	d.	 `close()`:
	⁃	 Tells the operating system that you are done with a file descriptor and closes the file pointed to by the file descriptor. 
	⁃	This function is defined in the `unistd.h` header file.
	⁃	Prototype: `int close(int fd);`
*/

CODING GET_NEXT_LINE:

	1.	Recall, the size of the buffer will be defined at compilation, so it’ll vary, and will be dependent on the user telling `read()` how many bytes of the file they want read.
	⁃	e.g. `cc -Wall -Wextra -Werror -D Buffer_size=42 <files>.c`.
	2.	Recall, calling `read()` in a loop on a file will overwrite the same buffer each time it stores the new bytes of characters read. 
	⁃	We need a remedy for this, e.g. we create a variable called “stash” so that the previously read bytes are not lost/overwritten. 
	3.	Recall, we need `get_next_line()` to retrieve a line that ends with a newline `\n`.
	⁃	So, we will need to check in our “stash” if a `\n` has been reached. 
	⁃	If no `\n` has been reached, then we continue to call `read()`. 
	⁃	Then it’ll read the next n bytes of characters, then increment the pointer n bytes forward, then store in the buffer the n bytes read, then if successful, return the number of bytes read. 
	⁃	Then put the characters read into the “stash”. 
	⁃	Then we look inside “stash” again to check if there is a `\n` in there. 
	⁃	If no `\n` has been reached, then we continue our work again and call `read()`. 
	⁃	If in our “stash” we did find a `\n` signaling a line break in our file, we then want to extract this line (a string of characters), from our reserve “stash”.
	⁃	In order to send this extracted line to `get_next_line()` for it to return to us, we will need a variable e.g. called “line”. 
	⁃	Our variable “line” will store the extracted characters we want, included the line break `\n` and the end. 
	⁃	Now that `get_next_line()` has returned us our first line of the file, we will need to clean up our “stash”, as what it had previously stored, was already returned, and we no longer need “stash” to store it. 
 already returned, and we no longer need “stash” to store it. 
	⁃	We need to call `get_next_line()` on the file we want read multiple times until all the lines have been read, one line at a time. 
	4.	Recall, when `read()` is called subsequently, the pointer to the buffer remains where it last completed its n bytes read, because it is associated with the file descriptor of that file.
	⁃	So, after our first line that was read and returned, even though we’d already cleaned up our “stash”, when we come back and call `get_next_line()` again, the “stash” variable is re-initialized, back to where the pointer was last left off. 
	⁃	Recall, a static variable is a variable that will keep its value between two function calls. 
	⁃	In this case, it will have stored everything that has been read. 
