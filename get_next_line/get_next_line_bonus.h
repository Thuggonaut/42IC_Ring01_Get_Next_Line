#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

#define MAX_FD 1024  // Maximum number of file descriptors

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char    *ft_substr(char const *s, unsigned int start, size_t len); 
char    *ft_strjoin(char *s1, char *s2); 
char	*ft_strdup(const char *str);
char    *process_line(char **stash); 
char    *read_from_fd(int fd);
char    *get_next_line_bonus(int fd); 

#endif
