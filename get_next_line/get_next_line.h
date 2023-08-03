#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 //Set a default buffer size in case it is not set at compile time
# endif

char    *ft_substr(char const *s, unsigned int start, size_t len); //Needed to extract from the `stash`, a portion of the string up to the `\n` character, and the remaining portion
char	*ft_strdup(const char *str);
char    *ft_strjoin(char *s1, char *s2); //Needed to join the "leftovers" in `stash` from the previously read `\n`, to the characters next read
char    *process_line(char **stash); 
char    *read_from_fd(int fd);
char    *get_next_line(int fd); //Our main function that will return a line extracted from a file

#endif
