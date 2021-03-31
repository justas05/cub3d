/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errors.h>
#include <config.h>
#include <utils.h>
#include <libft.h>

#include <unistd.h>
#include <mlx.h>

#include <dbg.h>
int		extract_texture(t_config *config, char *filename, unsigned int **dest)
{
	void	*img;
	int		tab[5];

	/*img = mlx_xpm_file_to_image(config->handle.mlx.ptr, filename,
								&tab[0], &tab[1]);
	if (img == NULL || tab[0] != IMG_WIDTH || tab[1] != IMG_HEIGHT)
		return (-1);
	*dest = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);*/
	return (*dest == NULL);
}

int		extract_resolution(char *line, t_config *config)
{
	line = atoi_s(skip_spaces(line), &config->handle.window.size.x);
	line = atoi_s(skip_spaces(line), &config->handle.window.size.y);
	return (*skip_spaces(line) ? E_CFG_RESOLUTION : 0);
}

int		extract_sprite_texture(char *line, t_config *config)
{
	return (extract_texture(config, skip_spaces(line), &config->s) ?
		E_CFG_S : 0);
}

int		extract_floor_color(char *line, t_config *config)
{
	if (*(line = skip_spaces(atoi_s(skip_spaces(line), &config->f.r))) != ',')
		return (E_CFG_F);
	++line;
	if (*(line = skip_spaces(atoi_s(skip_spaces(line), &config->f.g))) != ',')
		return (E_CFG_F);
	++line;
	line = skip_spaces(atoi_s(skip_spaces(line), &config->f.b));
	return (*line || !is_valid_rgb(&config->f) ? E_CFG_F : 0);
}

int		extract_ceilling_color(char *line, t_config *config)
{
	if (*(line = skip_spaces(atoi_s(skip_spaces(line), &config->c.r))) != ',')
		return (E_CFG_C);
	++line;
	if (*(line = skip_spaces(atoi_s(skip_spaces(line), &config->c.g))) != ',')
		return (E_CFG_C);
	++line;
	line = skip_spaces(atoi_s(skip_spaces(line), &config->c.b));
	return (*line  || !is_valid_rgb(&config->c)? E_CFG_C : 0);
}
