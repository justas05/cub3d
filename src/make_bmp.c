/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/20 13:13:21 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config.h>
#include <errors.h>
#include <utils.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	put_header(t_config *config, int fd)
{
	char	hdr[54];

	hdr[0] = 'B';
	hdr[1] = 'M';
	itoc(&hdr[2], config->screen.width * config->screen.height + 54);
	hdr[10] = 54;
	hdr[14] = 40;
	itoc(&hdr[18], config->screen.width);
	itoc(&hdr[24], config->screen.height);
	hdr[26] = 1;
	hdr[28] = config->screen.bits_per_pixel;
	return (write(fd, hdr, 54) < 54);
}

static int	put_image_to_file(t_config *config, int fd)
{
	int				i;
	int				j;
	unsigned int	clr;

	i = config->screen.height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < config->screen.width)
		{
			clr = *(unsigned int*)(config->screen.addr +
				(i * config->screen.size_line +
					j * (config->screen.bits_per_pixel / 8)));
			if (write(fd, &clr, sizeof(clr)) < (ssize_t)sizeof(clr))
				return (E_FILE_WRITE);
			++j;
		}
		--i;
	}
	return (0);
}

int	make_bmp(t_config *config)
{
	int	fd;
	int	err;

	err = 0;
	fd = open(SCREENSHORT_FILENAME, O_CREAT | O_WRONLY,
		S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (E_OPEN_FILE);
	if (!(put_header(config, fd) && put_image_to_file(config, fd)))
		err = E_FILE_WRITE;
	close(fd);
	return (err);
}
