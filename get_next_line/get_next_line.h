#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t  ft_strlen(const char *s); //Needed in `ft_strjoin()` and `ft_strdup()` to calculate the lengths of input strings to determine the size of the new strings that needs to be allocated by `malloc()`
char    *ft_strchr(const char *s, int c); //Needed to locate a character in a string. In the case of `get_next_line()`, we search for the `\n` character
char    *ft_strjoin(char *s1, char *s2); //Needed to join the characters remaining in `stash` from what had been read after the previous `\n`, to the characters next read, and stored in a temporary buffer 
char    *ft_substr(char const *s, unsigned int start, size_t len); //Needed to extract from the temporary buffer, a portion of the string up to the `\n` character. This will be the line that `get_line()` returns
char    *ft_strdup(const char *s); 
char    *ft_line_read(int fd, char *line, char **stash);
char    *ft_get_line(char **stash);
char    *get_next_line(int fd);

#endif
