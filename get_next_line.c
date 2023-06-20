/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgardine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:00:32 by fgardine          #+#    #+#             */
/*   Updated: 2023/05/24 18:05:00 by fgardine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*find_newline(char *linez);
char	*trim_excess(char *linez);
char	*get_next_line(int fd);
size_t	ft_strlen(const	char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgardine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:00:02 by fgardine          #+#    #+#             */
/*   Updated: 2023/05/24 21:05:20 by fgardine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freethings(char *str)
{
	free(str);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*malloc1(void)
{
	char	*s1;

	s1 = malloc(1 * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc1();
		if (s1 == NULL)
			return (NULL);
	}
	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr == NULL)
		return (freethings(s1));
	i = 0;
	j = 0;
	while (s1[j] != '\0')
		newstr[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	free(s1);
	if (newstr[0] == '\0')
		return (freethings(newstr));
	return (newstr);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgardine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:48:20 by fgardine          #+#    #+#             */
/*   Updated: 2023/05/25 22:11:01 by fgardine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_newline(char *linez)
{
	int		i;
	int		mal;
	char	*ret;

	mal = 1;
	i = 0;
	while (linez[i] && linez[i] != '\n')
		i++;
	if (linez[i] == '\n')
		mal = 2;
	ret = malloc(sizeof(char) * (i + mal));
	if (ret == NULL)
		return (NULL);
	ret[i + mal - 1] = '\0';
	while (i >= 0)
	{
		ret[i] = linez[i];
		i--;
	}
	return (ret);
}

char	*trim_excess(char *linez)
{
	int		i;
	int		b;
	char	*excess;

	i = 0;
	b = 0;
	while (linez[i] && linez[i] != '\n')
		i++;
	if (!linez[i])
	{
		free(linez);
		return (NULL);
	}
	excess = malloc(sizeof(char) * (ft_strlen(linez + i) + 1));
	if (excess == NULL)
	{
		free(linez);
		return (NULL);
	}
	i++;
	while (linez[i])
		excess[b++] = linez[i++];
	excess[b] = '\0';
	free(linez);
	return (excess);
}

char	*read_time(int fd, char *store)
{
	char	*buf;
	int		readbyte;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	readbyte = 1;
	while (!ft_strchr(store, '\n') && (readbyte != 0))
	{
		readbyte = read(fd, buf, BUFFER_SIZE);
		if (readbyte == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[readbyte] = '\0';
		store = ft_strjoin(store, buf);
	}
	free(buf);
	return (store);
}

char	*get_next_line(int fd)
{
	char		*lineret;
	static char	*store;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = read_time(fd, store);
	if (!store)
		return (NULL);
	lineret = find_newline(store);
	store = trim_excess(store);
	return (lineret);
}
/*
#include "fcntl.h"
int	main(void)
{
	int	file;

	file = open("coolNL", O_RDONLY);

	printf("GNL OUTPUT:%s", get_next_line(file));
	printf("GNL OUTPUT:%s", get_next_line(file));
	printf("GNL OUTPUT:%s", get_next_line(file));
	printf("GNL OUTPUT:%s", get_next_line(file));
	return(0);
}
*/


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgardine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:00:32 by fgardine          #+#    #+#             */
/*   Updated: 2023/05/24 21:53:34 by fgardine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*find_newline(char *linez);
char	*trim_excess(char *linez);
char	*get_next_line(int fd);
size_t	ft_strlen(const	char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgardine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:00:02 by fgardine          #+#    #+#             */
/*   Updated: 2023/05/24 21:05:20 by fgardine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freethings(char *str)
{
	free(str);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*malloc1(void)
{
	char	*s1;

	s1 = malloc(1 * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc1();
		if (s1 == NULL)
			return (NULL);
	}
	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr == NULL)
		return (freethings(s1));
	i = 0;
	j = 0;
	while (s1[j] != '\0')
		newstr[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	free(s1);
	if (newstr[0] == '\0')
		return (freethings(newstr));
	return (newstr);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgardine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:48:20 by fgardine          #+#    #+#             */
/*   Updated: 2023/05/25 22:12:34 by fgardine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_newline(char *linez)
{
	int		i;
	int		mal;
	char	*ret;

	mal = 1;
	i = 0;
	while (linez[i] && linez[i] != '\n')
		i++;
	if (linez[i] == '\n')
		mal = 2;
	ret = malloc(sizeof(char) * (i + mal));
	if (ret == NULL)
		return (NULL);
	ret[i + mal - 1] = '\0';
	while (i >= 0)
	{
		ret[i] = linez[i];
		i--;
	}
	return (ret);
}

char	*trim_excess(char *linez)
{
	int		i;
	int		b;
	char	*excess;

	i = 0;
	b = 0;
	while (linez[i] && linez[i] != '\n')
		i++;
	if (!linez[i])
	{
		free(linez);
		return (NULL);
	}
	excess = malloc(sizeof(char) * (ft_strlen(linez + i) + 1));
	if (excess == NULL)
	{
		free(linez);
		return (NULL);
	}
	i++;
	while (linez[i])
		excess[b++] = linez[i++];
	excess[b] = '\0';
	free(linez);
	return (excess);
}

char	*read_time(int fd, char *store)
{
	char	*buf;
	int		readbyte;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	readbyte = 1;
	while (!ft_strchr(store, '\n') && (readbyte != 0))
	{
		readbyte = read(fd, buf, BUFFER_SIZE);
		if (readbyte == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[readbyte] = '\0';
		store = ft_strjoin(store, buf);
	}
	free(buf);
	return (store);
}

char	*get_next_line(int fd)
{
	char		*lineret;
	static char	*store[500];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store[fd] = read_time(fd, store[fd]);
	if (!store[fd])
		return (NULL);
	lineret = find_newline(store[fd]);
	store[fd] = trim_excess(store[fd]);
	return (lineret);
}
/*
#include "fcntl.h"
int	main(void)
{
	int	file;

	file = open("coolNL", O_RDONLY);

	printf("GNL OUTPUT:%s", get_next_line(file));
	printf("GNL OUTPUT:%s", get_next_line(file));
	printf("GNL OUTPUT:%s", get_next_line(file));
	printf("GNL OUTPUT:%s", get_next_line(file));
	return(0);
}
*/
/*
 * this is almost exactly the same as my non bonus, the only difference
 * being that im including a [fd] with my static char pointer which 
 * means it can be independant with up to 500 different fd things
 */



