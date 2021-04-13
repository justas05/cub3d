/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <config.h>

char	*skip_spaces(char *line)
{
	if (line)
		while (ft_isblank(*line))
			++line;
	return (line);
}

char	*atoi_s(char *line, int *num)
{
	if (!num || !line)
		return (NULL);
	*num = 0;
	while (ft_isdigit(*line))
	{
		*num *= 10;
		*num += (*line++ - '0');
	}
	return (line);
}

int	is_valid_rgb(t_rgb *rgb)
{
	if (!rgb)
		return (0);
	return (0 <= rgb->r && rgb->r <= 255
		&& 0 <= rgb->g && rgb->g <= 255
		&& 0 <= rgb->b && rgb->b <= 255);
}
