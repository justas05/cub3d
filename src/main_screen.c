/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:59:43 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/25 00:34:07 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <config.h>

static t_point_i	texture_range(t_config *config, t_point_d *ray)
{
	/*t_point_d	delta_dist;
	t_point_d	side_dist;
	t_point_i	step;

	delta_dist = (t_point_d){abs(1 / ray->x), abs(1 / ray->y)};
	side_dist = (t_point_d){delta_dist.x * ((1 - 2 * (ray->x < 0)) *  + (ray->x > 0)),
		delta_dist.y * (1 - 2 * (ray->y < 0))};
	step = (t_point_i){1 - 2 * (ray->x < 0), 1 - 2 * (ray->y < 0)};
	while (!hit)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			wall_pos += step.x;
		}
	}*/
}

static void	fill(t_config *config, int pos, t_point_i p, t_trgb trgb)
{
	int	i;

	i = p.x;
	while (i < p.y)
	{
		mlx_pixel_put_local(config, pos, i, trgb);
		++i;
	}
}

void	main_screen(t_config *config)
{
	t_point_d	ray;
	double		k;
	int			j;

	j = 0;
	k = 2 * hypot(config->plane.x, config->plane.y)
		/ config->handle.window.size.x;
	while (j < config->handle.window.size.x / 2)
	{
		/*ray = (t_point_d){config->player.dir.x + k * j * config->plane.x,
			config->player.dir.y + k * j * config->plane.y};
		texture_range(config, &ray);
		ray = (t_point_d){config->player.dir.x - k * j * config->plane.x,
			config->player.dir.y - k * j * config->plane.y};
		texture_range(config, &ray);*/
		fill(config, j, (t_point_i){0, config->screen.height / 2 - 100}, config->f);
		fill(config, j,
			(t_point_i){config->screen.height / 2 + 100, config->screen.height}, config->c);
		++j;
	}
}
