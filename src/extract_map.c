/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/20 11:28:45 by hbooke           ###   ########.fr       */
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

static int	map_to_num_array(t_config *config)
{
	return (0);
}

static int	check_map(t_config *config)
{
	t_map_row	*r;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < config->map.row_count)
	{
		r = config->map.rows + i;
		j = 0;
		while (j < r->col_count)
		{
			printf("%c", r->cols[j]);
			++j;
		}
		printf("\n");
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
	return ((config->map.row_count <= 2 || check_map(config)) * E_MAP);
}
