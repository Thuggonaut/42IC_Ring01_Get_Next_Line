#include "get_next_line.h"

char *get_next_line(int fd) //Define a function that takes a file descriptor, and returns a pointer to a character array (the line retrieved) of the current `fd`
{
    static char *stash; //Declare a static character pointer to hold the remainder of a line after a `\n` is found
    char    *tmp_stash; //Declare a temporary variable in order to update the current stash to the new stash
    char    *line_read; //Declare a character pointer to hold the current line being read
    char    *line; //Declare a character pointer to store the extracted `line` from `stash` up to the `\n`

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0) //Check for errors. See #1
    {
		free(stash); //If any errors, free the buffer to prevent memory leaks
		stash = NULL; //Signal that the memory has been freed and is safe with a clean slate
	    return (NULL); //Return `NULL`
	}    
    if (!stash) //If the stash is not yet allocated (i.e., this is the first call to the function or the previous stash has been freed)
        stash = ft_strdup(""); //Allocate an empty string and assign it to `stash`. See #2
    line = process_line(&stash); //Extract a complete line from the stash
    if (line) //Checks if a complete line is found
        return (line); //If so, return the complete line. Otherwise, it returns `NULL`, indicating that more data needs to be read from the file descriptor, and proceeds to the next code
    line_read = read_from_fd(fd); //Allocate memory for the data read, read from the `fd`, then return the data read as `line_read`
    if (!line_read) //Checks if `line_read` is `NULL`, if so, it means that there is no more data to read from the `fd` (end-of-file or an error occurred)
    {
        line = ft_strdup(stash); //Copy the entire `stash` and assign it to `line`. This essentially checks if there is any data left in the stash. If there is data left in the stash, it means the file ended without a `\n`
        free(stash); //We no longer need the data in `stash` as it's already stored in `line`
        stash = NULL; //Ensure `stash` does not point to the now-deallocated memory, and become a "dangling pointer". See #3
        if (*line) //If `line` is not an empty string
            return (line); //Return the remaining data from the file
        free(line); //If `line` is an empty string, there is no more data to return. Free `line` and return `NULL`
        return (NULL); 
    }
    tmp_stash = ft_strjoin(stash, line_read); //If `line_read` is not `NULL`, it means more data was read from the `fd`. Concatenate the read data with the stash and update `stash` pointer accordingly
    free(stash); //Free memory before updating the new stash
    stash = tmp_stash; //Assign to the updated stash, the concatenated data
    free(line_read); //Free `line_read` as it's no longer needed
    return (get_next_line(fd)); //Recursively call itself `get_next_line(fd)` to continue reading and processing lines from the file descriptor. The process repeats until a complete line is found, or the end-of-file is reached. See #4
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
    }
    close(fd);
    return (0);
}
*/

/*
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


#2  This step is necessary to initialize stash to an empty string, which will be used to accumulate data read from the file descriptor. If stash is already 
    allocated (i.e., it's not NULL), we don't need to allocate a new empty string.


#3  A dangling pointer is a pointer that doesn't point to a valid object. 
    - If you have a pointer pointing to a memory location and that memory location is deallocated (for example, by using 
      `free()` in C), the pointer is now dangling. 
    - It's pointing to a memory location that has been freed and can be reused for other purposes.
    - Setting pointers to `NULL` after freeing the memory they point to, avoids returning pointers to local variables.
    - Since `get_next_line()` may continue to be called, if `stash` still points to the deallocated memory, it could lead to undefined behavior if the function 
      attempts to read or modify the memory at that location.
    - By setting `stash` to `NULL`, we ensure that any subsequent operations that rely on the `stash` being valid will not mistakenly access the freed memory.


#4  When there is no more data to read from the file, the final recursive call will eventually reach a point where it returns `NULL`. 
    - This is because the `read_from_fd` function returns `NULL` when there is no more data to read from the file descriptor, indicating the end of the file.
    - This `NULL` value will propagate back through the recursive calls until it reaches the initial call to `get_next_line`, effectively indicating the end 
      of the file.
        - The `NULL` return value from `get_next_line` is propagating back to the `line` variable within the while loop of the tester in `main()`. The loop 
          iterates as long as `get_next_line` returns a `non-NULL` value, indicating that there is more data to read from the file. Once get_next_line returns 
          `NULL`, the loop stops, and the code after the loop continues.
        - Recall, in the first iteration, `line = NULL`. 
*/