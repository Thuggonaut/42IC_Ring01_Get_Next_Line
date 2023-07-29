#include "get_next_line_bonus.h"

char *get_next_line_bonus(int fd) //Define a function that takes in integer (a file descriptor), and returns a pointer to a character array (the line retrieved) of the current `fd`
{
  static char *stash[MAX_FD]; //Declare an array of static character pointers with `MAX_FD` elements, to hold the remainder of a line corresponding to its `fd`, after a newline character is found. See 4.
  char *line; //Declare a character pointer to hold the current line being read
  
  if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || (!(line = malloc(sizeof(char) * (BUFFER_SIZE + 1))))) //Check for errors. The extra check here is `fd >= MAX_FD`
    return (NULL); //If any errors, return `NULL`
  return (ft_line_read(fd, line, &stash[fd])); //Returns the result of `ft_line_read()`. It reads a line from `fd` into `line`, stops when it encounters a `\n`, and stores any remaining text in `stash` for the current `fd`, before returning `line`
}

/*
TO TEST:

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;

    if (fd1 < 0 || fd2 < 0)
    {
        printf("Error opening files\n");
        return (1);
    }
    printf("Reading from file1.txt:\n");
    while ((line = get_next_line_bonus(fd1)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    printf("Reading from file2.txt:\n");
    while ((line = get_next_line_bonus(fd2)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd1);
    close(fd2);
    return (0);
}
*/

/*
RE BONUS PART:

1.  We are using the same codes as in the Mandatory part, with minor modifications.

2.  To meet the bonus part of `get_next_line`, our function needs to handle multiple file descriptors. (The other requirement of only 
    using one static variable, had already been implemented in the Mandatory part). 

3.  To achieve the handling of multiple file descriptors, the only difference from our Bonus part to the Mandatory, is that here, we 
    use an array of strings in our `static char` variable `stash`, instead of a single string. 
        - This means, that each string corresponds to a file descriptor. 
        - `ft_line_read()` is then called with the address of the `stash` string for the current file descriptor. 
4.  Here's a breakdown of `static char *stash[MAX_FD];`:
        1. `static`: 
            - This keyword means that the variable `stash` retains its value between function calls. 
            - Without `static`, `stash` would be reinitialized to its default value every time `get_next_line` is called. 
            - With `static`, once `stash` is initialized, it keeps its value until the program ends. 
            - This is crucial for `get_next_line` because it needs to remember the `stash` between calls.
        2. `char *`: 
            - This declares that the elements of the `stash` array are pointers to characters. 
            - In the context of get_next_line, each element of `stash` is a pointer to a dynamically allocated string that holds the 
              "leftover" characters from the last `read` operation for a particular file descriptor.
        3. `stash[MAX_FD]`: 
            - This declares `stash` as an array with `MAX_FD` elements. 
            - `MAX_FD` is a constant that represents the maximum number of file descriptors that your program is expected to handle. 
            - Each file descriptor has its own "stash" string, so `stash[fd]` is the `stash` string for file descriptor `fd`.
        4. So, in summary, `static char *stash[MAX_FD];` declares `stash` as a static array of `MAX_FD` pointers to characters. 
            - Each element of `stash` is a pointer to a string that holds the leftover characters from the last read operation for a 
              particular file descriptor.
*/