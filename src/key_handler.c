/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/19 17:19:05 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>
#include <garbage.h>

int	close_handler(t_config *config, int arg)
{
	free_config(config);
	exit(0);
}

static int	move_handler(t_config *config, int arg)
{
	return (0);
}

static int	sideway_handler(t_config *config, int arg)
{
	return (0);
}

static int	rotate_handler(t_config *config, int arg)
{
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
		action[3](params, 1);
	else if (k == K_LEFT)
		action[3](params, -1);
	return (0);
}
