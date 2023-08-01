#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 //Set a default buffer size in case it is not set at compile time
# endif

size_t  ft_strlen(const char *s); //Needed in `ft_strjoin()` and `ft_get_line` to calculate the lengths of input strings for `malloc()` to allocate new memory
char    *ft_substr(char const *s, unsigned int start, size_t len); //Needed to extract from the `stash`, a portion of the string up to the `\n` character, and the remaining portion
char    *ft_strjoin(char *s1, char *s2); //Needed to join the "leftovers" in `stash` from the previously read `\n`, to the characters next read
char    *ft_get_line(char **stash); //Needed  to extract a line from the `stash` string, when a `\n` is encountered
char    *ft_line_read(int fd, char *line, char **stash); //Needed to read data from a file descriptor and append it to the `stash` string until a `\n` is found
char    *get_next_line(int fd); //Our main function that will return a line extracted from a file

#endif
