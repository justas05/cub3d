/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 00:02:35 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 11:01:25 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errors.h>
#include <config.h>
#include <stdlib.h>

int	add_sprite(t_config *config, ssize_t i, ssize_t j)
{
	t_sprite	*s;

	s = malloc(sizeof(t_sprite));
	if (!s)
	{
		clear_sprites(config);
		return (E_UNKNOWN);
	}
	s->pos.x = j;
	s->pos.y = i;
	s->next = config->draw.sprites;
	config->draw.sprites = s;
	return (0);
}

void	clear_sprites(t_config *config)
{
	t_sprite	*walker;

	if (!config->draw.sprites)
		return ;
	while (config->draw.sprites)
	{
		walker = config->draw.sprites->next;
		free(config->draw.sprites);
		config->draw.sprites = walker;
	}
	config->draw.sprites = NULL;
}

void	draw_sprites(t_config *config)
{
	;
}
