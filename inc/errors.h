/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 08:28:10 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

enum		e_errors
{
	E_ARGS,
	E_FILE,
	E_CFG,
	E_CFG_RESOLUTION,
	E_CFG_NO,
	E_CFG_SO,
	E_CFG_WE,
	E_CFG_EA,
	E_CFG_S,
	E_CFG_F,
	E_CFG_C,
	E_MAP,
	E_EXT,
	E_WND,
	E_IMAGE,
	E_OPEN_FILE,
	E_FILE_WRITE,
	E_UNKNOWN
};

int	print_error(int err);

#endif
