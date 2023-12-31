#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif

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

char *process_line(char **stash) 
{
    int len;
    len = 0;
    while ((*stash)[len] != '\n' && (*stash)[len] != '\0')
        len++;
    if ((*stash)[len] == '\n') 
    {
        char *line = ft_substr(*stash, 0, len);
        char *leftovers = ft_substr(*stash, len + 1, strlen(*stash) - (len + 1));
        free(*stash);
        *stash = leftovers;
        return (line);
    }
    return (NULL);
}

char *read_from_fd(int fd) 
{
    char *line_read;
    int read_bytes;
    line_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!line_read) 
        return (NULL);
    read_bytes = read(fd, line_read, BUFFER_SIZE);
    if (read_bytes <= 0) 
    {
        free(line_read);
        return (NULL);
    }
    line_read[read_bytes] = '\0';
    return (line_read);
}

char *get_next_line(int fd)
{
    static char *stash;
    char *line_read;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
        return (NULL);
    if (!stash)
        stash = strdup("");
    line = process_line(&stash);
    if (line)
        return (line);
    line_read = read_from_fd(fd);
    if (!line_read) 
    {
        line = strdup(stash);
        free(stash);
        stash = NULL;
        if (*line) 
            return (line);
        free(line);
        return (NULL);
    }
    stash = ft_strjoin(stash, line_read);
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
