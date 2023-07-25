#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char *ft_strchr(const char *s, int c)
{
    while (*s != (char)c)
        if (!*s++)
            return (NULL);
    return (char *)s;
}

char *ft_strjoin(char *s1, char *s2)
{
    char *str;
    int i = 0;
    int j = 0;

    if (!s1 || !s2 || !(str = malloc(sizeof(*str) * (strlen(s1) + strlen(s2) + 1))))
        return (NULL);
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        str[i + j] = s2[j];
        j++;
    }
    str[i + j] = '\0';
    return (str);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *substr;
    size_t  i;

    if (!s || !(substr = malloc((len + 1) * sizeof(char))))
        return (NULL);
    i = 0;
    while (i < len && *(s + start + i))
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

    s_dup = (char *)malloc((strlen(s) + 1) * sizeof(char));
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
	char		*tmp;

	while (!(ft_strchr(line, '\n')) && (read_bytes = read(fd, line, BUFFER_SIZE)))
	{
		line[read_bytes] = '\0';
		tmp = *stash;
		*stash = ft_strjoin(tmp, line);
		free(tmp);
		tmp = NULL;
	}
	free(line);
	line = NULL;
	return (ft_get_line(stash));
}

char	*ft_get_line(char **stash)
{
	char		*line;
	char		*tmp;
	int			len;

	len = 0;
	while ((*stash)[len] != '\n' && (*stash)[len] != '\0')
		len++;
	if ((*stash)[len] == '\n')
	{
		line = ft_substr(*stash, 0, len);
		tmp = *stash;
		*stash = ft_strdup(&((*stash)[len + 1]));
		free(tmp);
		tmp = NULL;
	}
	else if ((*stash)[len] == '\0')
	{
		line = *stash;
		*stash = NULL;
	}
	return (line);
}
