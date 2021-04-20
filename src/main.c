/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/20 12:56:23 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <garbage.h>
#include <errors.h>
#include <config.h>
#include <check.h>

int	main(int argc, char **argv)
{
	t_config	config;
	int			err;

	err = 0;
	init_config(&config);
	config.handle.mlx.ptr = mlx_init();
	if (!config.handle.mlx.ptr
		|| check_args(argc, argv, &config)
		|| parse_config(&config)
		|| init(&config))
	{
		err = -1;
	}
	free_config(&config);
	return (err);
}
