#include "get_next_line.h"

char *get_next_line(int fd) //Define a function that takes in integer (a file descriptor), and returns a pointer to a character array (the line retrieved)
{
  static char *stash; //Declare a static character pointer to hold the remainder of a line after a newline character is found
  char *line; //Declare a character pointer to hold the current line being read
  
  if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || (!(line = malloc(sizeof(char) * (BUFFER_SIZE + 1))))) //Check for errors. See #1
    return (NULL);
  return (ft_line_read(fd, line, &stash));
}

/*
#1  This line of code checks for several potential error conditions before the program proceeds with reading from the file descriptor. If any of these 
    conditions are true, the function immediately returns `NULL` to indicate an error. Here's a breakdown of each condition:

    1. `fd < 0`: 
        - This checks if the file descriptor is negative. 
        - In Unix-like operating systems, file descriptors are non-negative integers that the system uses to identify open files. 
        - If `fd` is negative, it's not a valid file descriptor.

    2.  `BUFFER_SIZE <= 0`: 
        - This checks if `BUFFER_SIZE` is less than or equal to `0`. 
        - `BUFFER_SIZE` is a macro that should be defined elsewhere in your code, and it determines the number of bytes to read at a time from the file 
          descriptor. 
        - If `BUFFER_SIZE` is less than or equal to `0`, it's not possible to read from the file descriptor.
read(fd, NULL, 0) < 0: This is a call to the read function with fd as the file descriptor, NULL as the buffer to read into, and 0 as the number of bytes to read. This is effectively a "dry run" of the read function to check if reading from fd would cause an error. If read returns a negative value, it indicates an error, so the function returns NULL.
!(line = malloc(sizeof(char) * (BUFFER_SIZE + 1))): This is a call to the malloc function to allocate memory for line, which will hold the line of text read from the file descriptor. sizeof(char) * (BUFFER_SIZE + 1) calculates the number of bytes to allocate, which is enough to hold BUFFER_SIZE characters plus one extra for the null terminator. If malloc returns NULL, it means that the memory allocation failed, so the function returns NULL.
In summary, this line of code is checking for several potential error conditions related to the file descriptor, the buffer size, the ability to read from the file descriptor, and the ability to allocate memory. If any of these conditions are met, the function immediately returns NULL to indicate an error.
*/