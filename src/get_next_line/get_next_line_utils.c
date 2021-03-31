/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t		ft_strlen(const char *str)
{
	int res;

	res = 0;
	while (*str++)
		++res;
	return (res);
}

void		*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ptr;

	ptr = (unsigned char*)s;
	while (n--)
		if (*ptr != (unsigned char)c)
			++ptr;
		else
			return (ptr);
	return (NULL);
}

void		*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned char	*from;
	unsigned char	*to;

	from = (unsigned char *)src;
	to = (unsigned char *)dest;
	if (from < to)
	{
		from += num - 1;
		to += num - 1;
		while (num)
		{
			*to-- = *from--;
			--num;
		}
	}
	else if (from > to)
	{
		while (num)
		{
			*to++ = *from++;
			--num;
		}
	}
	return (dest);
}

void		*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	void	*res;

	res = NULL;
	if (!size)
		free(ptr);
	else if (!ptr)
		res = malloc(size);
	else if (size <= old_size)
		res = ptr;
	else if (ptr && size > old_size)
	{
		res = malloc(size);
		if (res)
		{
			ft_memmove(res, ptr, old_size);
			free(ptr);
		}
	}
	return (res);
}

void		*ft_flush(char **line, char *buf, size_t len)
{
	size_t	line_len;

	line_len = (*line) ? ft_strlen(*line) : 0;
	*line = (char*)ft_realloc(*line, line_len + 1, line_len + len + 1);
	if (*line)
	{
		ft_memmove(*line + line_len, buf, len);
		*(*line + line_len + len) = 0;
	}
	return (*line);
}
