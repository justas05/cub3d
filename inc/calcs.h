/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:18:03 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 13:29:44 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCS_H
# define CALCS_H

# include <config.h>

void	set_delta_distance(t_config *config);
void	set_vars(t_config *config);
int		set_side_distance(t_config *config);
void	set_wall_dist(t_config *config, int i);

#endif
