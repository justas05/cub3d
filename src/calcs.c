/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:49:43 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 22:01:29 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>
#include <math.h>

void	set_delta_distance(t_config *config)
{
	if (config->draw.ray.y == 0.0 || config->draw.ray.y == -0.0)
		config->draw.delta_dist.x = 0;
	else if (config->draw.ray.x == 0.0 || config->draw.ray.x == -0.0)
		config->draw.delta_dist.x = 1;
	else
		config->draw.delta_dist.x = fabs(1.0 / config->draw.ray.x);
	if (config->draw.ray.x == 0.0 || config->draw.ray.x == -0.0)
		config->draw.delta_dist.y = 0;
	else if (config->draw.ray.y == 0.0 || config->draw.ray.y == -0.0)
		config->draw.delta_dist.y = 1;
	else
		config->draw.delta_dist.y = fabs(1.0 / config->draw.ray.y);
}

void	set_vars(t_config *config)
{
	config->draw.map.x = (int)config->player.pos.x;
	config->draw.map.y = (int)config->player.pos.y;
	config->draw.step.x = 1 - 2 * (config->draw.ray.x < 0);
	config->draw.step.y = 1 - 2 * (config->draw.ray.y < 0);
	config->draw.side_dist.x = config->draw.delta_dist.x
		* ((1 - 2 * (config->draw.ray.x < 0))
			* (config->draw.map.x - config->player.pos.x)
			+ (config->draw.ray.x >= 0));
	config->draw.side_dist.y = config->draw.delta_dist.y
		* ((1 - 2 * (config->draw.ray.y < 0))
			* (config->draw.map.y - config->player.pos.y)
			+ (config->draw.ray.y >= 0));
}

int	set_side_distance(t_config *config)
{
	int			hit;
	int			side;

	hit = 0;
	while (!hit)
	{
		if (config->draw.side_dist.x < config->draw.side_dist.y)
		{
			config->draw.side_dist.x += config->draw.delta_dist.x;
			config->draw.map.x += config->draw.step.x;
			side = 0;
		}
		else
		{
			config->draw.side_dist.y += config->draw.delta_dist.y;
			config->draw.map.y += config->draw.step.y;
			side = 1;
		}
		hit = (config->map.rows[config->map.row_count - config->draw.map.y - 1]
				.cols[config->draw.map.x]
				== 1);
	}
	return (side);
}

void	set_wall_dist(t_config *config, int i)
{
	double	wall_temp;

	if (!config->draw.side)
		config->draw.wall_dist[i] = config->player.pos.y
			+ config->draw.p_w_dist * config->draw.ray.y;
	else
		config->draw.wall_dist[i] = config->player.pos.x
			+ config->draw.p_w_dist * config->draw.ray.x;
	wall_temp = config->draw.wall_dist[i] - (int)config->draw.wall_dist[i];
	config->draw.t_pos = (int)(wall_temp * IMG_HEIGHT);
	if ((!config->draw.side && (config->draw.ray.x > 0))
		|| (config->draw.side && config->draw.ray.y < 0))
		config->draw.t_pos = IMG_HEIGHT - config->draw.t_pos - 1;
	config->draw.tex_pos = (config->draw.range.x - config->handle.window.size.y
			/ 2 + config->draw.line_h / 2)
		* ((double)IMG_HEIGHT / config->draw.line_h);
}
