/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:59:43 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/26 15:16:46 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <config.h>
#include <utils.h>

static t_point_i	texture_range(t_config *config, t_point_d *ray)
{
	int			side;
	int			perp_wall_dist;
	int			hit;
	t_point_i	map;
	t_point_d	delta_dist;
	t_point_d	side_dist;
	t_point_i	step;

	map = (t_point_i){(int)config->player.pos.x, (int)config->player.pos.y};

	if (ray->y == 0.0)
		delta_dist.x = 0;
	else if (ray->x == 0.0)
		delta_dist.x = 1;
	else
		delta_dist.x = fabs(1.0 / ray->x);
	
	if (ray->x == 0.0)
		delta_dist.y = 0;
	else if (ray->y == 0.0)
		delta_dist.y = 1;
	else
		delta_dist.y = fabs(1.0 / ray->y);

	if (ray->x < 0)
	{
		step.x = -1;
		side_dist.x = (config->player.pos.x - map.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (-config->player.pos.x + 1.0 + map.x) * delta_dist.x;
	}
	
	if (ray->y < 0)
	{
		step.y = -1;
		side_dist.y = (config->player.pos.y - map.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (-config->player.pos.y + 1.0 + map.y) * delta_dist.y;
	}

	/*side_dist = (t_point_d){delta_dist.x * ((1 - 2 * (ray->x < 0)) * (map.x
		- (int)config->player.pos.x) + (ray->x > 0)),
		delta_dist.y * ((1 - 2 * (ray->y < 0)) * (map.y
		- (int)config->player.pos.y) + (ray->y > 0))};
	step = (t_point_i){1 - 2 * (ray->x < 0), 1 - 2 * (ray->y < 0)};*/
	hit = 0;
	while (!hit)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist.y;
			map.y += step.y;
			side = 1;
		}
		hit = (config->map.rows[config->map.row_count - map.y - 1].cols[map.x] != 0.0);
	}
	if (!side)
		perp_wall_dist = (map.x - config->player.pos.x + (1 - step.x) / 2) / ray->x;
	else
		perp_wall_dist = (map.y - config->player.pos.y + (1 - step.y) / 2) / ray->y;
	
	//Calculate height of line to draw on screen
	int lineHeight = (int)(config->handle.window.size.y / perp_wall_dist);

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + config->handle.window.size.y / 2;
	if(drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + config->handle.window.size.y / 2;
	if(drawEnd >= config->handle.window.size.y) drawEnd = config->handle.window.size.y - 1;
	
	return ((t_point_i){drawStart, drawEnd});
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

static void	fill_sky_floor(t_config *config, int j)
{
	int	half_height;
	int	half_width;

	half_height = config->screen.height / 2;
	half_width = config->handle.window.size.x / 2;
	fill(config, half_width + j, (t_point_i){0, half_height}, config->c);
	fill(config, half_width - j, (t_point_i){0, half_height}, config->c);
	fill(config, half_width + j,
		(t_point_i){half_height, config->screen.height}, config->f);
	fill(config, half_width - j,
		(t_point_i){half_height, config->screen.height}, config->f);
}

void	main_screen(t_config *config)
{
	t_point_d	ray;
	t_point_i	wall;
	double		k;
	int			j;
	int			half_height;
	int			half_width;

	j = 0;
	half_width = config->handle.window.size.x / 2;
	half_height = config->screen.height / 2;
	k = 2 * hypot(config->plane.x, config->plane.y)
		/ config->handle.window.size.x - 1;
	while (j < half_width)
	{
		fill_sky_floor(config, j);

		ray = (t_point_d){config->player.dir.x + k * j * config->plane.x,
			config->player.dir.y + k * j * config->plane.y};
		wall = texture_range(config, &ray);
		/*
		// fill(config, half_width + j, wall, w);
		ray = (t_point_d){config->player.dir.x - k * j * config->plane.x,
			config->player.dir.y - k * j * config->plane.y};
		wall = texture_range(config, &ray);*/
		// fill(config, config->handle.window.size.x / 2 - j, wall, w);
		++j;
	}
}
