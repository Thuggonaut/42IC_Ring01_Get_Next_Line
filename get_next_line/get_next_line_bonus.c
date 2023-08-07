#include "get_next_line_bonus.h"

char *get_next_line(int fd) 
{
    static char *stash[MAX_FD]; //Declare an array of static character pointers with `MAX_FD` elements, to hold the remainder of a line corresponding to its `fd`, after a newline character is found. See 4.
    char    *tmp_stash;    
    char    *line_read; 
    char    *line; 

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0) //Check for errors. The extra check here is `fd >= MAX_FD`
    {
        free(stash[fd]);
        stash[fd] = NULL;
        return (NULL);
    } 
    if (!stash[fd]) 
        stash[fd] = ft_strdup(""); 
    line = process_line(&stash[fd]); 
    if (line) 
        return (line); 
    line_read = read_from_fd(fd); 
    if (!line_read) 
    {
        line = ft_strdup(stash[fd]);
        free(stash[fd]);
        stash[fd] = NULL;
        if (*line) 
            return (line);
        free(line);
        return (NULL);
    }
    tmp_stash = ft_strjoin(stash[fd], line_read);
    free(stash[fd]);
    stash[fd] = tmp_stash;
    free(line_read);
    return (get_next_line(fd));
}

/*
TO TEST:

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1 = open("test1.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    char *line;

    if (fd1 < 0 || fd2 < 0)
    {
        printf("Error opening files\n");
        return (1);
    }
    printf("Reading from test1.txt:\n");
    while ((line = get_next_line_bonus(fd1)) != NULL)
    {
        printf("%s\n", line);
    }
    printf("Reading from test2.txt:\n");
    while ((line = get_next_line_bonus(fd2)) != NULL)
    {
        printf("%s\n", line);
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
        4. So, in summary, `static char *stash[MAX_FD];` declares `stash` as a static array of `MAX_FD` file pointers to characters. 
            - Each element of `stash` is a pointer to a string that holds the leftover characters from the last read operation for a 
              particular file descriptor.
*/
