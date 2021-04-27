/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 20:59:43 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/27 12:00:51 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <config.h>
#include <utils.h>
#include <calcs.h>

static void	distance(t_config *config)
{
	set_delta_distance(config);
	set_vars(config);
	config->draw.side = set_side_distance(config);
	if (!config->draw.side)
		config->draw.p_w_dist = (config->draw.map.x - config->player.pos.x
			+ (1 - config->draw.step.x) / 2) / config->draw.ray.x;
	else
		config->draw.p_w_dist = (config->draw.map.y - config->player.pos.y
			+ (1 - config->draw.step.y) / 2) / config->draw.ray.y;
	config->draw.line_h = (int)(config->handle.window.size.y /
		(config->draw.p_w_dist * (4.0 * config->handle.window.size.y)
		/ (3.0 * config->handle.window.size.x)));
	config->draw.range.x = (config->handle.window.size.y
		- config->draw.line_h) / 2;
	config->draw.range.x *= (config->draw.range.x >= 0);
	config->draw.range.y = (config->handle.window.size.y
		+ config->draw.line_h) / 2;
	if (config->draw.range.y >= config->handle.window.size.y)
		config->draw.range.y = config->handle.window.size.y - 1;
}

t_image	*get_texture(t_config *config)
{
	if (config->draw.side)
	{
		if (config->draw.step.y > 0)
			return (&config->no);
		if (config->draw.step.y < 0)
			return (&config->so);
	}
	else
	{
		if (config->draw.step.x > 0)
			return (&config->we);
		if (config->draw.step.x < 0)
			return (&config->ea);
	}
	return (&config->screen);
}

static void	fill(t_config *config, int x)
{
	int		j;

	j = 0;
	while (j < config->draw.range.x)
		mlx_pixel_put_local(config, x, j++, t_trgb_to_int(config->c));
	while (j < config->draw.range.y)
	{
		config->draw.tex_pos += ((double)IMG_HEIGHT / config->draw.line_h);
		mlx_pixel_put_local(config, x, j++,
			((int *)get_texture(config)->data)[IMG_WIDTH
				* ((int)config->draw.tex_pos & (IMG_HEIGHT - 1))
				+ config->draw.t_pos]);
	}
	while (j < config->handle.window.size.y)
		mlx_pixel_put_local(config, x, j++, t_trgb_to_int(config->f));
}

void	main_screen(t_config *config)
{
	double		k;
	int			j;

	j = 0;
	while (j < config->handle.window.size.x)
	{
		k = 2 * j / (double)config->handle.window.size.x - 1;
		config->draw.ray = (t_point_d){config->player.dir.x
			+ k * config->draw.plane.x,
			config->player.dir.y + k * config->draw.plane.y};
		distance(config);
		set_wall_dist(config);
		fill(config, j);
		++j;
	}
}
