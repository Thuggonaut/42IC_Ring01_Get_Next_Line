#include "get_next_line.h"

size_t ft_strlen(const char *s) //Define a function that takes a pointer to a string, and returns its number of characters up to but not including the null character ('\0')
{
    size_t i; //Declare a `size_t` variable to be used as a counter. `size_t` is used because we need an unsigned integer type that can represent sizes, counts and indices

    i = 0; //Initialised to `0` as no count has been processed
    while (*s) //Loop until the end of the string is reached
    {
        i++; //Add `1` to our count
        s++; //Move to the next character for counting
    }    
    return (i); //Return the number of characters in the string counted
}

char *ft_strchr(const char *s, int c) //Define a function that takes a pointer to a string, an integer that represents a char, and returns a pointer to the first occurrence of the character `c` in the string `s`
{
    while (*s != (char)c) //Loop as long as the current character in the string is not the character we are searching for. `c` is casted to `char` to make comparison possible
        if (!*s++) //Move to the next character in the string for processing in the next loop, and check if it is the `\0`
            return (NULL); //However if the end of the string has been reached, `NULL` is returned because `c` hasn't been found
    return (char *)s; //If `c` has been found, return a pointer to the found character in `s`
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

char	*ft_get_line(char **stash) //Define a function that takes a pointer to a string array (a pointer to a pointer to a character), and returns an extracted `line` 
{
	char		*line; //Declare a pointer variable that will store a pointer to the extracted `line` from the `stash` string
	char		*tmp_buff; //Declare a temporary pointer variable that will store the old `stash`, while the new `stash` needs updating
	int			len; //Declare an integer variable to keep track of the length of `line`

	len = 0; //Iniatialised to `0` because no extraction has taken place yet
	while ((*stash)[len] != '\n' && (*stash)[len] != '\0') //Increment `len` until a `\n` is found, and the end of `stash` has been reached, to traverse through `stash`
		len++; //By the end of the loop, `len` will hold the length of the line in `stash` up to the `\n` or the end of the string
	if ((*stash)[len] == '\n') //Check if a `\n` has been encountered at the end of `stash`, if so, perform the below operations
	{
		line = ft_substr(*stash, 0, len); //Assign to `line`, a new string created by `ft_substr()` that contains the characters from the start of `stash` (0-th index) up to, but not including, the `\n`
		tmp_buff = *stash; //Assign to `tmp_buff` the characters from `stash` before `stash` is updated next
		*stash = ft_substr(*stash, len + 1, ft_strlen(*stash) - (len + 1)); //`stash` is updated to be a new string that starts from the character after the `\n` in the old stash, until the end of the old stash
		free(tmp_buff); //Free the old `stash` now stored in `tmp_buff`. See #3
		tmp_buff = NULL;
	}
	else if ((*stash)[len] == '\0') //Check if a `\0` has been encountered at the end of `stash`, if so, perform the below operations
	{
		line = *stash; //Assign to `line` the pointer to the new `stash` which contains all the remaining characters in `stash`
		*stash = NULL; //Set to `NULL` because there are no characters left in `stash` to process. See #4
	}
	return (line); //Return the line that was extracted from `stash`
}

char	*ft_line_read(int fd, char *line, char **stash)
{
	int			read_bytes;
	char		*tmp_buff;

	while (!(ft_strchr(line, '\n')) && (read_bytes = read(fd, line, BUFFER_SIZE)))
	{
		line[read_bytes] = '\0';
		tmp_buff = *stash;
		*stash = ft_strjoin(tmp_buff, line);
		free(tmp_buff);
		tmp_buff = NULL;
	}
	free(line);
	line = NULL;
	return (ft_get_line(stash));
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


#3  The `tmp_buff` is used to hold the original `stash` string while a new `stash` string is being created.
        - A new block of memory is allocated for the new `stash` string by `ft_substr()`, and the stash pointer is updated to point to
          this new block of memory. 
        - However, the original `stash` string is still occupying a block of memory, and this block of memory is no longer accessible 
          because no pointers are pointing to it. This is what's known as a memory leak.
        - To prevent this memory leak, the `tmp_buff` pointer is used to keep a reference to the original `stash` string before the 
          `stash` pointer is updated. 
        - Then, once the new `stash` string has been created, the original `stash` string can be safely freed using the `tmp_buff` 
          pointer.
        - By freeing the `tmp_buff`, you're freeing the memory that was originally allocated for the `stash` string, preventing a memory
          leak. 
        - Setting `tmp_buff` to `NULL` afterwards is a good practice to avoid dangling pointers.
                - A dangling pointer is a pointer that doesn't point to a valid object. 
                - If you have a pointer pointing to a memory location and that memory location is deallocated (for example, by using 
                  `free()` in C), the pointer is now dangling. 
                - It's pointing to a memory location that has been freed and can be reused for other purposes.
                - Setting pointers to `NULL` after freeing the memory they point to, avoids returning pointers to local variables.


#4  Setting `*stash` to `NULL` serves two purposes:
    
    1. Avoid dangling pointers: `
        - After `line` has taken the remaining characters of `stash`, the memory previously pointed to by `stash is now owned by `line`. 
        - To avoid having `stash` become a dangling pointer (a pointer that points to memory it doesn't own), it's set to `NUL`L.

    2. Indicate the end of data: 
        - Setting `stash` to `NULL` also serves as an indicator that all data has been processed and there's nothing left in `stash`. 
        - If a subsequent call to `ft_get_line()` is made, it can check if `stash` is `NULL` and, if so, know immediately that there's
          no more data to process.
*/