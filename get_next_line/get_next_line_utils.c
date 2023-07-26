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
    while (i < len && *(s + start + i)) //Loop as long as there are more characters to copy (i < len), and 
    {
        *(substr + i) = *(s + start + i);
        i++;
    }
    *(substr + i) = '\0';
    return (substr);
}

char *ft_strdup(const char *s)
{
    char *s_dup;
    int i;

    s_dup = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
    if (!s_dup)
        return (NULL);
    i = 0;
    while (s[i])
    {
        s_dup[i] = s[i];
        i++;
    }
    s_dup[i] = '\0';
    return (s_dup);
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

char	*ft_get_line(char **stash)
{
	char		*line;
	char		*tmp_buff;
	int			len;

	len = 0;
	while ((*stash)[len] != '\n' && (*stash)[len] != '\0')
		len++;
	if ((*stash)[len] == '\n')
	{
		line = ft_substr(*stash, 0, len);
		tmp_buff = *stash;
		*stash = ft_strdup(&((*stash)[len + 1]));
		free(tmp_buff);
		tmp_buff = NULL;
	}
	else if ((*stash)[len] == '\0')
	{
		line = *stash;
		*stash = NULL;
	}
	return (line);
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
*/