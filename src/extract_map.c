/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/22 10:46:04 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <config.h>
#include <errors.h>
#include <get_next_line.h>

static int	add_new_map_line(t_map *map, size_t len)
{
	if (!map)
		return (E_MAP);
	map->rows = ft_realloc(map->rows, map->row_count * sizeof(t_map_row),
			(map->row_count + 1) * sizeof(t_map_row));
	if (!map->rows)
		return (E_MAP);
	(map->rows + map->row_count)->cols = NULL;
	(map->rows + map->row_count)->col_count = len;
	++map->row_count;
	return (0);
}

static int	extract_map_line(t_config *config, char *line,
	size_t len, size_t *max_len_line)
{
	if (!len || !line)
		return (0);
	if (add_new_map_line(&config->map, len))
		return (E_MAP);
	if (max_len_line && len > *max_len_line)
		*max_len_line = len;
	(config->map.rows + config->map.row_count - 1)->cols = ft_strdup(line);
	return (((config->map.rows + config->map.row_count - 1)->cols == NULL)
		* E_MAP);
}

static char	get_num_for_char(char c)
{
	char	code;

	code = N_SPACE;
	if (c == C_NORTH)
		code = N_NORTH;
	else if (c == C_EAST)
		code = N_EAST;
	else if (c == C_SOUTH)
		code = N_SOUTH;
	else if (c == C_WEST)
		code = N_WEST;
	else if (c == C_SPRITE)
		code = N_SPRITE;
	else if (c == C_WALL)
		code = N_WALL;
	else if (c == C_EMPTY)
		code = N_EMPTY;
	else if (c != C_SPACE)
		code = N_ERR;
	return (code);
}

int	map_to_num_array(t_config *config, size_t len)
{
	char	*new_row;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < config->map.row_count)
	{
		j = 0;
		new_row = malloc(len * sizeof(char));
		if (!new_row)
			return (E_MAP);
		while (j < (config->map.rows + i)->col_count)
		{
			new_row[j] = get_num_for_char((config->map.rows + i)->cols[j]);
			if (new_row[j++] == N_ERR)
				return (E_MAP);
		}
		while (j < len)
			new_row[j++] = -1;
		free((config->map.rows + i)->cols);
		(config->map.rows + i)->col_count = len;
		(config->map.rows + i)->cols = new_row;
		++i;
	}
	return (0);
}

int	extract_map(int fd, char *line, t_config *config)
{
	int		ret;
	size_t	max_len_line;

	ret = 1;
	max_len_line = 0;
	while (!extract_map_line(config, line, ft_strlen(line), &max_len_line)
		&& ret > 0)
	{
		free(line);
		line = NULL;
		ret = get_next_line(fd, &line);
	}
	free(line);
	return ((config->map.row_count <= 2
			|| map_to_num_array(config, max_len_line)
			|| check_map(config)) * E_MAP);
}
