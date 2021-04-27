/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/27 10:55:21 by hbooke           ###   ########.fr       */
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

int	is_valid_rgb(t_trgb *trgb)
{
	if (!trgb)
		return (0);
	return (0 <= trgb->t && trgb->t <= 255
		&& 0 <= trgb->r && trgb->r <= 255
		&& 0 <= trgb->g && trgb->g <= 255
		&& 0 <= trgb->b && trgb->b <= 255);
}

void	mlx_pixel_put_local(t_config *config, int w, int h, int color)
{
	char	*dst;

	dst = config->screen.data
		+ (h * config->screen.size_line
			+ w * (config->screen.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	t_trgb_to_int(t_trgb num)
{
	return ((num.t << 24) | (num.r << 16) | (num.g << 8) | (num.b));
}
