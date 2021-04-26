/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/25 10:48:08 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <config.h>

char	*skip_spaces(char *line);
char	*atoi_s(char *line, int *num);
int		is_valid_rgb(t_trgb *rgb);
void	itoc(char *buf, int num);
void	mlx_pixel_put_local(t_config *config, int w, int h, t_trgb color);

#endif
