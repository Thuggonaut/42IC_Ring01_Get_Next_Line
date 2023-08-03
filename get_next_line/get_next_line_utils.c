#include "get_next_line.h"

size_t ft_strlen(const char *s) //Define a function that takes a pointer to a string, and returns its number of characters up to but not including the null character ('\0')
{
    const char *start; //Declare a pointer variable that will store a pointer pointing to the start of `s` 

    start = s; //Assign to `start` the pointer pointing to `s`
    while (*s++) //This while loop does not need to have any executions inside `{}` brackets. It will loop until the end of `s` is reached, and in each iteration it post-increments the pointer to the next character
      ;
    return (s - start - 1); //`s` is now pointing to the end of `s`. The resulting length of `s` is calulated by subtracting the final position of `start` of the string (index `0`) from the position of `s`. The `-1` is to account for the extra increment for the `\0`
}

void *ft_memset(void *ptr, int value, size_t num) //Define a function that takes a pointer to the memory block to be filled, an integer value to set each byte, and a size_t number of bytes to be set to the given value
{
    unsigned char *p; //`unsigned char` is declared to ensure that we can access individual bytes of memory, as `unsigned char` allows us to set values in the range of 0 to 255

    p = (unsigned char *)ptr; //Assign the value of the `ptr` parameter
    while (num > 0) //Loop until `num` becomes `0`, at which point the function has set the specified number of bytes in memory to the given value
    {
        *p = (unsigned char)value; //Set the byte to the input value
        p++; //Move to the next byte in memory for processing
        num--; //Decremented to track the number of bytes remaining to be set
    }
    return (ptr); //Return the original pointer, which now points to the memory block with its content modified
}

void	*ft_calloc(size_t n, size_t size) //Define a function that takes a `size_t` number of elements to allocate memory for, the size for each element (see #1), and returns a generic pointer to the memory block
{
	void	*ptr; //Declare a generic pointer variable that will store a pointer to the memory block later allocated by `malloc()`

	ptr = malloc(n * size); //Assign to `ptr` a memory block 
	if (ptr != NULL) //If memory allocation is successfull, perform the following operations
		ft_memset(ptr, 0, n * size); //Initialise the allocated memory block to `0` in all elements. 
	return ((void *)ptr); //A pointer to the allocated memory block is returned. If allocation was unsuccessfull, `ptr` will be a `NULL` pointer
}

void	*ft_memcpy(void *dest, const void *src, size_t n) //Define a function that takes a pointer to the destination to be copied be copied, a pointer to the source from which to copy (`const` because we don't want to modify source), and the number of bytes to be copied
{
	unsigned char	*d; //Declare pointers used to traverse the destination and source memory blocks
	unsigned char	*s; //`unsigned char*` allows us to work with individual bytes rather than entire data types, which makes it easier to manipulate memory

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src) //Checks for valid pointers
		return (NULL); //If either is `NULL`, it means there is no valid memory location to copy data from or to, so the function returns `NULL`
	while (n--) //Loop `n` times
		*d++ = *s++; //Copy one byte at a time from the `src` to the `dest` memory locations. Post increment each iteration to move to the next chracters for copying
	return (dest); //Return the original `dest` pointer which will have the contents of `src`
}

char *ft_substr(char const *s, unsigned int start, size_t len) //Define a function that takes a pointer to a string, an integer representing the starting index from where to copy, the length of characters to copy, and returns a pointer to the extracted string
{
    char    *substr; //Declare a char pointer variable that will store a pointer to the extracted portion of a string
    size_t  i; //Declare a size_t variable that will be used as a counter to keep track of the number of characters copied from `s` to `substr` and ensures no more characters than specified by `len` are copied

    i = 0; //Initialised to `0` because no copying has been done
    if (!s || !(substr = malloc((len + 1) * sizeof(char)))) //Checks for an invalid input string `s`, and whether memory allocation has failed
        return (NULL); //If either are true, return `NULL`
    while (i < len && *(s + start + i)) //Loop as long as there are more characters to copy (i < len), and the `i-th` character of `s` from the `start` position is not `\n`
    {
        *(substr + i) = *(s + start + i); //Copy the `i-th` character from the `start` position in `s` to the `i-th` position in `substr`. See #2
        i++; //Move to the next character in `s`, and the next index in `substr` for processing
    }
    *(substr + i) = '\0'; //Ensure the new string is properly null terminated
    return (substr); //Return a pointer to the begining of the new string
}

char	*ft_strdup(const char *str) //Define a function that takes a pointer to a string to duplicate
{
	size_t	len; //Declare a size_t variabl to store the length of the input string str, including the null terminator
	char	*dst;

	len = ft_strlen(str) + 1; //Assign the length of `str` plus one to accommodate the null terminator in the duplicated string
	dst = ft_calloc(len, sizeof(char)); //Allocate memory for the duplicated string 
	if (dst == NULL) //Checks for memory allocation fail
		return (NULL); //Return `NULL` if so
	ft_memcpy(dst, str, len); //Copy into `dst`, the contents of `str`
	return (dst); //Return a pointer to the new dynamically allocated string that is an exact duplicate of the `str`
}

char *ft_strjoin(char *s1, char *s2) //Define a function that takes pointers to two strings, concatenate the strings, and return a pointer to a newly created and allocated string that consists of the joined two strings
{
    size_t len1; //Declare a variable to store the length of the first string
    size_t len2; //Declare a variable to store the length of the second string
    char *str; //Declare a pointer variable that will store a pointer to a newly allocated string, which the function later returns
    char *p; //Declare a pointer variable used to traverse and fill in the memory, while `str` holds the starting address of the allocated memory. See #1

    len1 = ft_strlen(s1); //Assign the length of the first string
    len2 = ft_strlen(s2); //Assign the length of the second string
    str = malloc((len1 + len2 + 1) * sizeof(*str)); //Allocate memory for the new string, ensuring enough space to copy both strings, plus `1` to account for the `\0`
    if (!str) //If memory allocation fails
        return (NULL); //Return `NULL`
    p = str; //Assign the pointer pointing to the start of `str` to the start of `p`
    while (*s1) //Loop until the end of `s1` is reached
        *p++ = *s1++; //Copy the current character of `s1` into the current index of `p`
    while (*s2) //Loop until the end of `s2` is reached
        *p++ = *s2++; //Copy the current character of `s2` into the current index of `p`
    *p = '\0'; //Ensure the new string is properly null terminated
    return (str); //Return the pointer which remains pointed at the beginning of the newly created string
}

char *process_line(char **stash) //Define a function that takes a pointer to a string array (a pointer to a pointer to a character), and returns the extracted `line` that is up to the `\n`
{
    int len; //Declare an integer variable to keep track of the length of `line` needed for extraction
    char *line; //Declare a pointer to a string, where the extrtacted `line` will be stored
    char *leftovers;

    len = 0; //Iniatialised to `0` because no extraction has taken place yet
    while ((*stash)[len] != '\n' && (*stash)[len] != '\0') //Increment `len` until a `\n` is found, or the end of `stash` has been reached, to traverse through `stash`
        len++; //By the end of the loop, `len` will hold the length of the line in `stash` up to the `\n` or the end of the string
    if ((*stash)[len] == '\n') //Check if a `\n` has been encountered at the end of `stash`, if so, perform the below operations
    {
        line = ft_substr(*stash, 0, len); //Extract the `line` that is up to the `\n`
        leftovers = ft_substr(*stash, len + 1, ft_strlen(*stash) - (len + 1)); //Extract the remaining chracters from `stash` after the `\n`
        free(*stash); //Now that we've extracted the `line` and `leftovers` portions from `stash` we no longer need this data. This "old stash" needs to be cleaned up for a "new stash"
        *stash = leftovers; //Update the "new stash" to contain only the remaining chracters from `stash`. This will be used by `get_next_line` to append the next line read
        return (line); //Return the line extracted up to the `\n`
    }
    return (NULL); //If a `\n` is not found, a complete line is not present in the stash. `NULL` to indicates that a complete line isn't available yet
}

char *read_from_fd(int fd) //Define a function that takes a file descriptor, and returns a pointer to a character array (the line retrieved) of the current `fd`
{
    char *line_read; //Declare a pointer to a string, where the retrieved line read from the current `fd` will be stored
    int read_bytes; //Declare an integer variable that will store the number of bytes read from the file descriptor

    line_read = malloc(sizeof(char) * (BUFFER_SIZE + 1)); //Allocated memory for the storage of the line retrieved
    if (!line_read) //Checks for successful allocation
        return (NULL); //Return NULL if not
    read_bytes = read(fd, line_read, BUFFER_SIZE); //Assign to `read_bytes`, the number of bytes succeffully read
    if (read_bytes <= 0) //If bytes read is `-1`, an error has occurred or `0` if there is no more data to read from `fd`. See #3
    {
        free(line_read); //Free this memory block for a new allocation
        return (NULL); //Return NULL due to error or no more data to read
    }
    line_read[read_bytes] = '\0'; //Ensure `line_read` is properly null terminated as `read()` does not add a `\0` at the end of the data it reads
    return (line_read); //Return the line of size `BUFFER_SIZE` retrieved from the current `fd`
}


/*
#1  Using a pointer `p` to traverse, rather than directly using `str` to traverse:
    - `str` points to the memory location obtained by the `malloc` call. This memory location is the base address of our new concatenated string. This 
      pointer is returned at the end of the function.
    - `p` starts at the same position as `str` but move along as we fill the memory with characters from `s1` and `s2`.
    - If we used `str` directly and incremented it, we'd lose the original pointer address for the allocated memory. That's not good because:
        - We'd have a memory leak: 
          Because we wouldn't be able to free the allocated memory later as we've lost the address of the start of that memory.
        - We wouldn't be able to return the beginning of the newly created string: 
          The requirement of `ft_strjoin` is to return a new string which is the concatenation of `s1` and `s2`. If we move `str` while putting in 
          characters, at the end of the function `str` would point to the end of the new string, not the beginning. 


#2  C allows various operations to be performed on pointers which includes addition, subtraction, comparison etc., but it doesn't allow operations like 
    multiplication or division. Addition and subtraction operations on pointers are special in the way they work. This is a very common practice in C where 
    there is a need to navigate arrays or manipulate strings, because strings in C are essentially arrays of characters.

    Let's break down *(substr + i) = *(s + start + i);:

    1. `substr + i and s + start + i`: 
        - In both of these expressions, `substr` and `s` are pointers which are being added to the integers `i` and `start + i` respectively. 
        - This is called pointer arithmetic.
        - When an integer is added to a pointer, it doesn't simply add the integer value to the memory address contained in the pointer. 
                - Instead, it adds the integer multiplied by the size of the data type the pointer points to. 
                - If `substr` is a pointer to a char, and the size of char is `1 byte`, then `substr + i` adds `i` bytes to the memory address contained 
                  in `substr`. 
                - This effectively moves the pointer `i` positions forward in an array of char.

    2. `*(substr + i) and *(s + start + i)`: 
        - The '*' operator is used here for dereferencing the pointer. 
        - It returns the value stored in the memory location pointed to by the pointer.
        - So `*(substr + i)` gives the `i-th` character from the begining of `substr`, and 
        - `*(s + start + i)` gives the `i-th` character from the `start` position in `s`.


#3  `read_bytes = read(fd, line, BUFFER_SIZE)`: 
    - This is a call to the `read` function, which reads up to `BUFFER_SIZE` bytes of data from the file descriptor `fd` into the buffer 
      pointed to by `line`. 
    - The `read` function returns the number of bytes actually read, or `-1` if an error occurred or there's no data to read. 
    - The result is stored in the `read_bytes` variable.
*/
