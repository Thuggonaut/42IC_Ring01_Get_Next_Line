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
7. Compile you code as follows (e.g. with a buffer size of 42):
   `cc -Wall -Wextra -Werror -D Buffer_size=42 <files>.c`
8. `get_next_line()` will be considered as having an undefined behaviour if the file pointed to by the file descriptor changed since the last call whereas `read()` didn't reach the end of the file.
9. `get_next_line()` will also be considered as having an undefined behaviour when reading a binary file.
    - however, you may choose to implement a logical way to handle this behaviour.
10. Consider, whether your function will work if the `BUFFER_SIZE` value is `9999`, `1`, or `10000000`, and why it is so.

Forbidden:
- Your libft library
- `lseek()
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
7. The `-D BUFFER_SIZE` flag




