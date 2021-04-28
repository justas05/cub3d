/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 10:52:08 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>
#include <stdlib.h>

#include <mlx.h>

static void	destroy_textures(t_config *config)
{
	if (config->no.addr)
		mlx_destroy_image(config->handle.mlx.ptr, config->no.addr);
	if (config->so.addr)
		mlx_destroy_image(config->handle.mlx.ptr, config->so.addr);
	if (config->we.addr)
		mlx_destroy_image(config->handle.mlx.ptr, config->we.addr);
	if (config->ea.addr)
		mlx_destroy_image(config->handle.mlx.ptr, config->ea.addr);
	if (config->s.addr)
		mlx_destroy_image(config->handle.mlx.ptr, config->s.addr);
}

static void	free_map(t_config *config)
{
	if (config->map.rows)
	{
		while (config->map.row_count--)
			if ((config->map.rows + config->map.row_count)->cols)
				free((config->map.rows + config->map.row_count)->cols);
		free(config->map.rows);
	}
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	if (config->config_filename)
		free(config->config_filename);
	if (config->screen.addr)
		mlx_destroy_image(config->handle.mlx.ptr, config->screen.addr);
	destroy_textures(config);
	clear_sprites(config);
	free_map(config);
	if (config->handle.mlx.ptr)
	{
		if (config->handle.window.ptr)
			mlx_destroy_window(config->handle.mlx.ptr,
				config->handle.window.ptr);
		free(config->handle.mlx.ptr);
	}
	init_config(config);
}
