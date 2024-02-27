/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_uils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tquemato <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:24:29 by tquemato          #+#    #+#             */
/*   Updated: 2023/08/07 01:30:04 by tquemato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	const char	*start;

	start = s;
	while (*s++)
		;
	return (s - start - 1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dst);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dst;

	len = ft_strlen(str) + 1;
	dst = (char *)malloc(len * sizeof(char));
	if (dst == NULL) 
		return (NULL);
	ft_memcpy(dst, str, len);
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	substr = malloc((len + 1) * sizeof(char));
	if (!s || !substr)
		return (NULL);
	while (i < len && *(s + start + i))
	{
		*(substr + i) = *(s + start + i);
		i++;
	}
	*(substr + i) = '\0';
	return (substr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;
	char	*p;

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
