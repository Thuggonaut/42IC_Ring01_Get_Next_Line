Mandatory part:

Create a function called get_next_line() that takes in a file descriptor to read from, and returns a line read from the file descriptor. 

Note:
- Repeated calls (e.g., using a loop) to your `get_next_line()` should let you read the text file pointed to by the file descriptor, one line at a time. 
- `get_next_line()` should return the line that was read, otherwise `NULL` if there is nothing else to read, or an error occured. 
    - The returned line should include the terminating `\n` character, except if the end of the file was reached and does not end with a `\n`.
- `get_next_line()` should work both when reading a file, and when reading from the standard input.
- The header file `get_next_line.h` must contain the prototype of `get_next_line()`.
- Add all needed helper functions in the get_next_line_utils.c file. 

Static Variables:

Structure of directories/files:
get_next_line/
  - get_next_line.c
  - get_next_line_utils.c
  - get_next_line.h

Prototype:
`char  *get_next_line(int fd);`

