#include "get_next_line_bonus.h"

size_t ft_strlen(const char *s)  
{
    const char *start;  

    start = s;  
    while (*s++)  
      ;
    return (s - start - 1);  
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

char *ft_strjoin(char *s1, char *s2)  
{
    size_t len1;  
    size_t len2; 
    char *str; 
    char *p; 

    len1 = ft_strlen(s1);  
    len2 = ft_strlen(s2);  
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
		*stash = ft_substr(*stash, len + 1, ft_strlen(*stash) - (len + 1));  
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

char	*ft_line_read(int fd, char *line_read, char **stash)  
{
	int			read_bytes; 
	char		*tmp_buff; 

	while ((read_bytes = read(fd, line_read, BUFFER_SIZE)))
	{
		line_read[read_bytes] = '\0'; 
		tmp_buff = *stash; 
		*stash = ft_strjoin(tmp_buff, line_read); 
		free(tmp_buff);
		tmp_buff = NULL;
	}
	free(line_read); 
	line_read = NULL; 
	return (ft_get_line(stash));
}
