#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

#define MAX_FD 1024  // Maximum number of file descriptors

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t  ft_strlen(const char *s); 
char    *ft_strchr(const char *s, int c); 
char    *ft_strjoin(char *s1, char *s2); 
char    *ft_substr(char const *s, unsigned int start, size_t len); 
char    *ft_get_line(char **stash); 
char    *ft_line_read(int fd, char *line, char **stash); 
char    *get_next_line_bonus(int fd); 

#endif
