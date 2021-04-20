/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/20 11:56:21 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errors.h>
#include <stdio.h>

const char *const	g_errors[] = {
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
	"cannot create window",
	"cannot create image",
	"cannot open file",
	"cannot write to file",
	"unknown error"
};

void	print_error(int err)
{
	if (!(0 <= err && err < E_UNKNOWN))
		err = E_UNKNOWN;
	printf("Error\n%s\n", g_errors[err]);
}
