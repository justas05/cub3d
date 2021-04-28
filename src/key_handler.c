/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 18:48:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include <config.h>
#include <garbage.h>

int	close_handler(t_config *config, int arg)
{
	(void)arg;
	free_config(config);
	exit(0);
}

static int	move_handler(t_config *config, int arg)
{
	t_point_d	pos;
	double		k;

	k = arg * config->player.speed
		/ hypot(config->player.dir.x, config->player.dir.y);
	pos = (t_point_d){config->player.pos.x + k * config->player.dir.x,
		config->player.pos.y + k * config->player.dir.y};
	if (!(config->map.rows[(int)(config->map.row_count - pos.y)]
		.cols[(int)pos.x] == 1 || config->map.rows[(int)(config->map.row_count
			- pos.y)].cols[(int)pos.x] == 2))
		config->player.pos = pos;
	return (0);
}

static int	sideway_handler(t_config *config, int arg)
{
	t_point_d	pos;
	double		k;

	k = arg * config->player.speed
		/ hypot(config->draw.plane.x, config->draw.plane.y);
	pos = (t_point_d){config->player.pos.x + k * config->draw.plane.x,
		config->player.pos.y + k * config->draw.plane.y};
	if (config->map.rows[(int)(config->map.row_count - 1 - pos.y)]
		.cols[(int)pos.x] != 1 && config->map.rows[(int)(config->map.row_count
		- pos.y)].cols[(int)pos.x] != 2)
		config->player.pos = pos;
	return (0);
}

static int	rotate_handler(t_config *config, int arg)
{
	double	x;

	x = config->player.dir.x;
	config->player.dir.x = x * cos(arg * config->angle)
		- config->player.dir.y * sin(arg * config->angle);
	config->player.dir.y = config->player.dir.y * cos(arg * config->angle)
		+ x * sin(arg * config->angle);
	x = config->draw.plane.x;
	config->draw.plane.x = x * cos(arg * config->angle)
		- config->draw.plane.y * sin(arg * config->angle);
	config->draw.plane.y = config->draw.plane.y * cos(arg * config->angle)
		+ x * sin(arg * config->angle);
	return (0);
}

int	key_handler(int k, void *params)
{
	const t_action	action[] = {close_handler, move_handler,
			sideway_handler, rotate_handler};

	if (k == K_ESC)
		action[0](params, 0);
	else if (k == K_W)
		action[1](params, 1);
	else if (k == K_S)
		action[1](params, -1);
	else if (k == K_A)
		action[2](params, -1);
	else if (k == K_D)
		action[2](params, 1);
	else if (k == K_RIGHT)
		action[3](params, -1);
	else if (k == K_LEFT)
		action[3](params, 1);
	return (0);
}
