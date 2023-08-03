#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *stash;
    char *line_read;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return (NULL);
    if (!stash)
        stash = ft_strdup("");
    line = process_line(&stash);
    if (line)
        return (line);
    line_read = read_from_fd(fd);
    if (!line_read) 
    {
        line = ft_strdup(stash);
        free(stash);
        stash = NULL;
        if (*line) 
            return (line);
        free(line);
        return (NULL);
    }
    stash = ft_strjoin(stash, line_read);
    free(line_read);
    return (get_next_line(fd));
}


char *get_next_line(int fd) //Define a function that takes a file descriptor, and returns a pointer to a character array (the line retrieved) of the current `fd`
{
  static char *stash; //Declare a static character pointer to hold the remainder of a line after a newline character is found
  char *line_read; //Declare a character pointer to hold the current line being read
  
  if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || (!(line_read = malloc(sizeof(char) * (BUFFER_SIZE + 1))))) //Check for errors. See #1
    return (NULL); //If any errors, return `NULL`
  return (ft_line_read(fd, line_read, &stash)); //Returns the result of `ft_line_read()` which is the `line` up to the `\n`. See #2
}

/*
TO TEST:

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test1.txt", O_RDONLY);
    char *line;

    if (fd < 0 )
    {
        printf("Error opening files\n");
        return (1);
    }
    printf("Reading from test1.txt:\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
*/

/*
RE `BUFFER_SIZE`:
    - You can change the buffer size at compilation. When you compile the C source code, the -D option will set a preprocessor macro. 
    - Compile your code like this, e.g. with buffer size of 42:

        `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c`

    - Then, the `BUFFER_SIZE` macro is given the value '42', and it can be used in your program. 
            - A `BUFFER_SIZE` of `1` means that you're reading in a file `1` byte at a time, which is very inefficient but can be useful for 
              testing your program. 
            - A `BUFFER_SIZE` of `10000000` means you're reading in the file `10000000` bytes at a time, which might be faster but 
              will use a lot more memory.


#1  This line of code checks for several potential error conditions before the program proceeds with reading from the file descriptor. If any of these 
    conditions are true, the function immediately returns `NULL` to indicate an error. Here's a breakdown of each condition:

    1. `fd < 0`: 
        - This checks if the file descriptor is negative. 
        - In Unix-like operating systems, file descriptors are non-negative integers that the system uses to identify open files. 
        - If `fd` is negative, it's not a valid file descriptor.

    2.  `BUFFER_SIZE <= 0`: 
        - This checks if `BUFFER_SIZE` is less than or equal to `0`. 
        - `BUFFER_SIZE` is a macro that specifies the size of the buffer used to read data from the file. 
		    - If `BUFFER_SIZE` is `0`, it means that the buffer size is not properly set, and thus the function cannot proceed to read from the file.

    3. `read(fd, NULL, 0) < 0`: 
        - This is a call to the `read` function with `fd` as the file descriptor, `NULL` as the buffer to read into, and `0` as the number of bytes to read. 
        - This is effectively a "dry run" of the `read` function to check if reading from `fd` would cause an error. 
        - If `read` returns a negative value, it indicates an error.

    4. `line = malloc(sizeof(char) * (BUFFER_SIZE + 1)))`: 
        - This is a call to the `malloc` function to allocate memory for `line`, which will hold the line of text read from the file descriptor. 
        - `sizeof(char) * (BUFFER_SIZE + 1)` calculates the number of bytes to allocate, which is enough to hold `BUFFER_SIZE` characters plus one extra 
          for the null terminator. 
        - If `malloc` returns `NULL`, it means that the memory allocation failed.


#2  Here's the breakdown of `ft_line_read(fd, line, &stash)`:

    1. `fd`: 
        - This is the file descriptor from which the function will read. It's the same file descriptor that was passed to get_next_line.

    2. `line`: 
        - This is a pointer to a block of memory that was allocated in `get_next_line()`. 
        - The `ft_line_read` function will store the line it reads from the file descriptor here.

    3. `&stash`: 
        - This is a pointer to the stash variable from `get_next_line()`. 
        - Since `stash` is a pointer, `&stash` is a pointer to a pointer. 
        - This allows `ft_line_read()` to modify `stash` to point to any remaining text after the newline character.
*/