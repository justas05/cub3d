/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 13:31:59 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>
#include <errors.h>

static int	check_full_config(t_config *config)
{
	return (!(config->player.pos.x > 0.0 && config->player.pos.y > 0.0
			&& config->no.addr && config->no.data
			&& config->so.addr && config->so.data
			&& config->we.addr && config->we.data
			&& config->ea.addr && config->ea.data
			&& config->s.addr && config->s.data
			&& config->c.r >= 0 && config->c.g >= 0 && config->c.b >= 0
			&& config->f.r >= 0 && config->f.g >= 0 && config->f.b >= 0
			&& config->handle.window.size.x > 0
			&& config->handle.window.size.y > 0));
}

int	init(t_config *config)
{
	if (!config || check_full_config(config))
		return (print_error(E_CFG));
	config->screen.addr = mlx_new_image(config->handle.mlx.ptr,
			config->screen.width, config->screen.height);
	config->draw.wall_dist = malloc(config->screen.width * sizeof(double));
	if (!config->screen.addr || !config->draw.wall_dist)
		return (print_error(E_IMAGE));
	config->screen.data = mlx_get_data_addr(config->screen.addr,
			&config->screen.bits_per_pixel, &config->screen.size_line,
			&config->screen.endian);
	if (config->save)
		return (make_bmp(config));
	config->handle.window.ptr = mlx_new_window(config->handle.mlx.ptr,
			config->handle.window.size.x, config->handle.window.size.y,
			WINDOW_TITLE);
	if (!config->handle.window.ptr)
		return (print_error(E_WND));
	mlx_key_hook(config->handle.window.ptr, key_handler, config);
	mlx_hook(config->handle.window.ptr, CROSS_BUTTON, 1, close_handler, config);
	mlx_loop_hook(config->handle.mlx.ptr, game, config);
	mlx_loop(config->handle.mlx.ptr);
	return (0);
}

int	game(t_config *config)
{
	main_screen(config);
	if (config->handle.window.ptr && config->screen.addr)
		mlx_put_image_to_window(config->handle.mlx.ptr,
			config->handle.window.ptr, config->screen.addr, 0, 0);
	return (0);
}
