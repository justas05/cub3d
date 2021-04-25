/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/24 20:48:19 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include <libft.h>
#include <errors.h>
#include <config.h>

int	check_args(int argc, char **argv, t_config *config)
{
	int	len;

	if (argc < 2 || argc > 3
		|| (argc == 3 && ft_strcmp("--save", argv[2]))
		|| (argc == 2 && ((len = ft_strlen(argv[1])) < 4
				|| ft_strcmp(S_EXT, argv[1] + len - 4))))
	{
		print_error(E_ARGS);
		return (-1);
	}
	config->save = (argc == 3);
	config->config_filename = ft_strdup(argv[1]);
	return (0);
}

static int	is_player(char c)
{
	return (c == N_SOUTH || c == N_EAST || c == N_WEST || c == N_NORTH);
}

static int	validate_field(t_config *config, ssize_t i, ssize_t j)
{
	if (((config->map.rows + i)->cols[j] != N_WALL
			&& (config->map.rows + i)->cols[j] != N_SPACE
			&& (i == (ssize_t)config->map.row_count - 1
				|| j == (ssize_t)(config->map.rows + i)->col_count - 1
			|| i == 0 || j == 0
			|| (config->map.rows + i)->cols[j + 1] == N_SPACE
			|| (config->map.rows + i)->cols[j - 1] == N_SPACE
			|| (config->map.rows + i + 1)->cols[j] == N_SPACE
			|| (config->map.rows + i - 1)->cols[j] == N_SPACE))
		|| (is_player((config->map.rows + i)->cols[j])
			&& config->player.pos.x > 0 && config->player.pos.y > 0))
		return (E_MAP);
	return (0);
}

static void	set_player(t_config *config, ssize_t i, ssize_t j, char c)
{
	config->player.pos.x = (double)j + 0.5;
	config->player.pos.y = config->map.row_count - 1.0 - (double)i + 0.5;
	if (c == N_SOUTH)
		config->player.dir = (t_point_d){0, -1};
	else if (c == N_EAST)
		config->player.dir = (t_point_d){1, 0};
	else if (c == N_WEST)
		config->player.dir = (t_point_d){-1, 0};
	else if (c == N_NORTH)
		config->player.dir = (t_point_d){0, 1};
	config->plane.x = sqrt(2.0 / 3.0) * config->player.dir.y;
	config->plane.y = -sqrt(2.0 / 3.0) * config->player.dir.x;
}

int	check_map(t_config *config)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	while (i < (ssize_t)config->map.row_count)
	{
		j = 0;
		while (j < (ssize_t)(config->map.rows + i)->col_count)
		{
			if (validate_field(config, i, j))
				return (E_MAP);
			else if (is_player((config->map.rows + i)->cols[j]))
				set_player(config, i, j, (config->map.rows + i)->cols[j]);
			++j;
		}
		++i;
	}
	return ((config->player.pos.x == 0.0 && config->player.pos.y == 0.0)
		* E_MAP);
}
