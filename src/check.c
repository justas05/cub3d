/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errors.h>
#include <config.h>

int	check_args(int argc, char **argv, t_config *config)
{
	int	len;

	if (argc < 2 || argc > 3
		|| (argc == 3 && ft_strcmp("--save", argv[2]))
		|| (argc == 2 && ((len = ft_strlen(argv[1])) < 4
				|| ft_strcmp(S_EXT, argv[1] + len - 4))))
	{
		print_error(E_ARGS);
		return (-1);
	}
	config->save = (argc == 3);
	config->config_filename = ft_strdup(argv[1]);
	return (0);
}
