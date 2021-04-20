/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exctractor1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/20 13:50:10 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errors.h>
#include <config.h>
#include <utils.h>
#include <libft.h>

#include <unistd.h>
#include <mlx.h>

int	extract_texture(t_config *config, char *filename, t_image *texture)
{
	texture->addr = mlx_xpm_file_to_image(config->handle.mlx.ptr,
			filename, &texture->width, &texture->height);
	if (texture->addr == NULL || texture->width != IMG_WIDTH
		|| texture->height != IMG_HEIGHT)
		return (-1);
	texture->data = (unsigned int *)mlx_get_data_addr(texture->addr,
			&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	return (0);
}

int	extract_resolution(char *line, t_config *config)
{
	int	width;
	int	height;

	line = atoi_s(skip_spaces(line), &width);
	config->handle.window.size.x = width;
	line = atoi_s(skip_spaces(line), &height);
	config->handle.window.size.y = height;
	mlx_get_screen_size(config->handle.mlx.ptr, &width, &height);
	if (config->handle.window.size.x > width
		|| config->handle.window.size.x <= 0)
		config->handle.window.size.x = width;
	if (config->handle.window.size.y > height
		|| config->handle.window.size.y <= 0)
		config->handle.window.size.y = height;
	config->screen.width = config->handle.window.size.x;
	config->screen.height = config->handle.window.size.y;
	return ((*skip_spaces(line) != '\0') * E_CFG_RESOLUTION);
}

int	extract_sprite_texture(char *line, t_config *config)
{
	return ((extract_texture(config, skip_spaces(line), &config->s) != 0)
		* E_CFG_S);
}

int	extract_floor_color(char *line, t_config *config)
{
	line = skip_spaces(atoi_s(skip_spaces(line), &config->f.r));
	if (*line != ',')
		return (E_CFG_F);
	line = skip_spaces(atoi_s(skip_spaces(++line), &config->f.g));
	if (*line != ',')
		return (E_CFG_F);
	line = skip_spaces(atoi_s(skip_spaces(++line), &config->f.b));
	return ((*line || !is_valid_rgb(&config->f)) * E_CFG_F);
}

int	extract_ceilling_color(char *line, t_config *config)
{
	line = skip_spaces(atoi_s(skip_spaces(line), &config->c.r));
	if (*line != ',')
		return (E_CFG_C);
	line = skip_spaces(atoi_s(skip_spaces(++line), &config->c.g));
	if (*line != ',')
		return (E_CFG_C);
	line = skip_spaces(atoi_s(skip_spaces(++line), &config->c.b));
	return ((*line || !is_valid_rgb(&config->c)) * E_CFG_C);
}
