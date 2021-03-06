/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 21:35:49 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include <errors.h>
#include <config.h>
#include <libft.h>
#include <get_next_line.h>
#include <utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	parse_line(char *line, t_config *config)
{
	int					i;
	const char			*strs[] = {"NO", "SO", "EA", "WE",
		"R", "S", "F", "C", NULL};
	const t_extract		extract[] = {extract_north_texture,
						extract_south_texture,
						extract_east_texture,
						extract_west_texture,
						extract_resolution,
						extract_sprite_texture,
						extract_floor_color,
						extract_ceilling_color};

	i = 0;
	line = skip_spaces(line);
	if (!line || !*line)
		return (0);
	while (strs[i])
	{
		if (ft_strnstr(line, strs[i], ft_strlen(strs[i])))
		{
			return (extract[i](skip_spaces(line + strlen(strs[i])), config));
		}
		++i;
	}
	return (E_CFG);
}

static void	cratch(t_config *config, int *err, int *ret, int *fd)
{
	*err = 0;
	*ret = 1;
	*fd = open(config->config_filename, O_RDONLY);
}

int	parse_config(t_config *config)
{
	int		err;
	int		ret;
	int		fd;
	char	*line;

	cratch(config, &err, &ret, &fd);
	if (!config || fd < 0)
		return (print_error(E_FILE));
	while (ret > 0 && !err)
	{
		line = NULL;
		ret = get_next_line(fd, &line);
		err = parse_line(line, config);
		if (err == E_CFG)
			err = extract_map(fd, line, config);
		else
			free(line);
	}
	if (err)
		print_error(err);
	close(fd);
	return (err);
}

void	init_config(t_config *config)
{
	if (!config)
		return ;
	ft_bzero(config, sizeof(t_config));
	config->player.speed = 0.1;
	config->angle = 5 * M_PI / 180;
	config->c = (t_trgb){0, -1, -1, -1};
	config->f = (t_trgb){0, -1, -1, -1};
}
