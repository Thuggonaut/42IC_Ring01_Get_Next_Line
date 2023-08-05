#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define MAX_FD 1024  

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5 
# endif

char *ft_strjoin(char *s1, char *s2)  
{
    size_t len1;  
    size_t len2; 
    char *str; 
    char *p; 

    len1 = strlen(s1);  
    len2 = strlen(s2);  
    str = malloc((len1 + len2 + 1) * sizeof(*str));  
    if (!str)  
        return (NULL);  
    p = str; 
    while (*s1) 
        *p++ = *s1++;  
    while (*s2)  
        *p++ = *s2++;  
    *p = '\0';  
    return (str);  
}

char *ft_substr(char const *s, unsigned int start, size_t len)  
{
    char    *substr;  
    size_t  i; 

    i = 0;  
    if (!s || !(substr = malloc((len + 1) * sizeof(char))))  
        return (NULL);  
    while (i < len && *(s + start + i))  
    {
        *(substr + i) = *(s + start + i); 
        i++;  
    }
    *(substr + i) = '\0';  
    return (substr);  
}

char    *get_next_line(int fd)
{
    static char *stash[MAX_FD];
    char        *line_read;
    char        *leftovers;
    char        *line;
    int         read_bytes;
    int         len;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 ) 
        return (NULL);
    
     if (!stash[fd])
        stash[fd] = strdup("");

    line_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!line_read)
        return (NULL);

    read_bytes = read(fd, line_read, BUFFER_SIZE);
    line_read[read_bytes] = '\0';
    stash[fd] = ft_strjoin(stash[fd], line_read);
   
    len = 0;
    while (stash[fd][len] != '\n' && stash[fd][len] != '\0')
        len++;

    if (stash[fd][len] == '\n')
    {
        line = ft_substr(stash[fd], 0, len);
        leftovers = ft_substr(stash[fd], len + 1, strlen(stash[fd]) - (len + 1));
        free(stash[fd]);
        stash[fd] = leftovers;
        free(line_read);
        return (line);
    }
    if (read_bytes == 0) 
    {
        if (*stash[fd]) 
        {
            line = strdup(stash[fd]);
            free(stash[fd]);
            stash[fd] = NULL;
            free(line_read);
            return (line);
        }
        free(stash[fd]);
        stash[fd] = NULL;
        free(line_read);
        return (NULL);
    }
    free(line_read);
    return (get_next_line(fd));
}

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
        free(line);
    }
    close(fd);
    return (0);
}
