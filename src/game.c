/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/24 21:01:59 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>
#include <errors.h>

int	init(t_config *config)
{
	if (!config)
		return (E_CFG);
	config->screen.addr = mlx_new_image(config->handle.mlx.ptr,
		config->screen.width, config->screen.height);
	if (!config->screen.addr)
		return (E_IMAGE);
	config->screen.data = mlx_get_data_addr(config->screen.addr,
		&config->screen.bits_per_pixel, &config->screen.size_line,
		&config->screen.endian);
	if (config->save)
		return (make_bmp(config));
	config->handle.window.ptr = mlx_new_window(config->handle.mlx.ptr,
		config->handle.window.size.x, config->handle.window.size.y, WINDOW_TITLE);
	if (!config->handle.window.ptr)
		return (E_WND);
	mlx_key_hook(config->handle.window.ptr, key_handler, config);
	mlx_hook(config->handle.window.ptr, CROSS_BUTTON, 1, close_handler, config);
	mlx_loop_hook(config->handle.mlx.ptr, game, config);
	mlx_loop(config->handle.mlx.ptr);
	return (0);
}

int	game(t_config *config)
{
	//move(config);
	main_screen(config);
	//draw_sprites(config);
	if (config->handle.window.ptr && config->screen.addr)
		mlx_put_image_to_window(config->handle.mlx.ptr,
			config->handle.window.ptr, config->screen.addr, 0, 0);
	return (0);
}
