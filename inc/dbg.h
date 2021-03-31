/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DBG_H
# define DBG_H

# define DBG_INFO fprintf(stderr, "[DEBUG:%s:%d]: ", __FILE__, __LINE__)
# define DBG_PRINT(x...) {DBG_INFO; fprintf(stderr, x); fprintf(stderr, "\n");}

#endif
