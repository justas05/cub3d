/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errors.h>
#include <stdio.h>

const char *const		g_errors[] = {
	"incorrect arguments",
	"something went wrong with file",
	"incorrect config file",
	"incorrect resolution",
	"incorrect NO texture",
	"incorrect SO texture",
	"incorrect WE texture",
	"incorrect EA texture",
	"incorrect sprite texture",
	"incorrect floor color",
	"incorrect ceiling color",
	"incorrect map",
	"incorrect extension",
	"unknown error"
};

void	print_error(int err)
{
	if (!(0 <= err && err < E_UNKNOWN))
		err = E_UNKNOWN;
	printf("Error\n%s\n", g_errors[err]);
}
