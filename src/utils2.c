/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:18:12 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 22:06:37 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	swap_byte(unsigned char *c1, unsigned char *c2)
{
	unsigned char	t;

	t = *c1;
	*c1 = *c2;
	*c2 = t;
}

void	swap(void *p1, void *p2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		swap_byte(p1 + i, p2 + i);
		++i;
	}
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
