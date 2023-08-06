#include "get_next_line_bonus.h"

size_t ft_strlen(const char *s)  
{
    const char *start;  

    start = s;  
    while (*s++)  
      ;
    return (s - start - 1);  
}

void *ft_memset(void *ptr, int value, size_t num)
{
    unsigned char *p;

    p = (unsigned char *)ptr;
    while (num > 0)
    {
        *p = (unsigned char)value;
        p++;
        num--;
    }
    return (ptr); 
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	ptr = malloc(n * size);
	if (ptr != NULL)
		ft_memset(ptr, 0, n * size);
	return ((void *)ptr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
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

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(str) + 1;
	dst = ft_calloc(len, sizeof(char));
	if (dst == NULL) 
		return NULL;
	ft_memcpy(dst, str, len);
	return dst;
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

char *process_line(char **stash) 
{
    char *line;
	char *leftovers;
	int len;
    len = 0;
	
    while ((*stash)[len] != '\n' && (*stash)[len] != '\0')
        len++;
    if ((*stash)[len] == '\n') 
    {
        line = ft_substr(*stash, 0, len);
        leftovers = ft_substr(*stash, len + 1, ft_strlen(*stash) - (len + 1));
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
