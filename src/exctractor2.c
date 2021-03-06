/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>
#include <errors.h>
#include <utils.h>

int	extract_north_texture(char *line, t_config *config)
{
	return ((extract_texture(config, skip_spaces(line), &config->no) != 0)
		* E_CFG_NO);
}

int	extract_south_texture(char *line, t_config *config)
{
	return ((extract_texture(config, skip_spaces(line), &config->so) != 0)
		* E_CFG_SO);
}

int	extract_west_texture(char *line, t_config *config)
{
	return ((extract_texture(config, skip_spaces(line), &config->we) != 0)
		* E_CFG_WE);
}

int	extract_east_texture(char *line, t_config *config)
{
	return ((extract_texture(config, skip_spaces(line), &config->ea) != 0)
		* E_CFG_EA);
}
