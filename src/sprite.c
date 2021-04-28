/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 00:02:35 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 22:08:33 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errors.h>
#include <config.h>
#include <utils.h>
#include <stdlib.h>
#include <math.h>

int	add_sprite(t_config *config, ssize_t i, ssize_t j)
{
	t_sprite	*s;

	s = malloc(sizeof(t_sprite));
	if (!s)
	{
		clear_sprites(config);
		return (E_UNKNOWN);
	}
	s->pos.x = 0.5 + j;
	s->pos.y = config->map.row_count - 1 + 0.5 - i;
	s->distance = 0.0;
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

void	sprite_calc(t_config *config, t_point_d d, t_sprite *s)
{
	double			inv_det;
	const t_point_i	w = config->handle.window.size;
	const t_point_d	p = config->player.dir;

	inv_det = 1.0 / (config->draw.plane.x * p.y - p.x * config->draw.plane.y);
	s->f.x = inv_det * (p.y * d.x - p.x * d.y);
	s->f.y = inv_det * (-config->draw.plane.y * d.x
			+ config->draw.plane.x * d.y);
	s->pos_x = (int)(w.x / 2 * (1 + s->f.x / s->f.y));
	s->height = abs((int)(w.y / (s->f.y * (4.0 * w.y / (3.0 * w.x)))));
	s->from.y = (-s->height / 2 + w.y / 2);
	s->from.y *= (s->from.y >= 0);
	s->to.y = (s->height / 2 + w.y / 2);
	if (s->to.y >= w.y)
		s->to.y = w.y - 1;
	s->width = abs((int)(w.y / (s->f.y * (4.0 * w.y / (3.0 * w.x)))));
	s->from.x = -s->width / 2 + s->pos_x;
	s->from.x *= (s->from.x >= 0);
	s->to.x = s->width / 2 + s->pos_x;
	if (s->to.x >= w.x)
		s->to.x = w.x - 1;
}

void	put_sprites(t_config *config, t_sprite *s)
{
	int			s_order;
	t_point_i	tex;
	int			clr;
	int			j;

	s_order = s->from.x - 1;
	while (++s_order < s->to.x)
	{
		tex.x = (int)(256 * ((s_order - (-s->width / 2 + s->pos_x)))
				* 64 / s->width) / 256;
		if (s->f.y > 0 && s_order > 0 && s_order < config->handle.window.size.x
			&& min(s->f.x, s->f.y) < config->draw.wall_dist[s_order])
		{
			j = s->from.y - 1;
			while (++j < s->to.y)
			{
				tex.y = ((j * 256 - config->handle.window.size.y * 128
							+ s->height * 128) * 64 / s->height) / 256;
				clr = ((int *)config->s.data)[(int)(64 * tex.y + tex.x)];
				if ((clr & 0x00FFFFFF) != 0)
					mlx_pixel_put_local(config, s_order, j, clr);
			}
		}
	}
}

void	sort_sprites(t_config *config)
{
	t_sprite	*walker;
	t_sprite	*walker2;

	walker = config->draw.sprites;
	while (walker)
	{
		walker2 = walker->next;
		while (walker2)
		{
			if (walker->distance < walker2->distance)
			{
				swap(&walker->distance, &walker2->distance, sizeof(double));
				swap(&walker->f, &walker2->f, sizeof(t_point_d));
				swap(&walker->from, &walker2->from, sizeof(t_point_d));
				swap(&walker->height, &walker2->height, sizeof(int));
				swap(&walker->pos, &walker2->pos, sizeof(t_point_d));
				swap(&walker->pos_x, &walker2->pos_x, sizeof(int));
				swap(&walker->to, &walker2->to, sizeof(t_point_d));
				swap(&walker->width, &walker2->width, sizeof(double));
			}
			walker2 = walker2->next;
		}
		walker = walker->next;
	}
}
