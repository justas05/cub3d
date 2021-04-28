/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 22:06:48 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <config.h>

char	*skip_spaces(char *line);
char	*atoi_s(char *line, int *num);
int		is_valid_rgb(t_trgb *rgb);
int		t_trgb_to_int(t_trgb num);
void	mlx_pixel_put_local(t_config *config, int w, int h, int color);
void	swap(void *p1, void *p2, size_t size);
double	min(double a, double b);

#endif
