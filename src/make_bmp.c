/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/27 10:56:59 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <config.h>
#include <errors.h>
#include <utils.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	itoc(char *buf, int num)
{
	if (buf)
	{
		buf[3] = (num >> 24) & 0xFF;
		buf[2] = (num >> 16) & 0xFF;
		buf[1] = (num >> 8) & 0xFF;
		buf[0] = num & 0xFF;
	}
}

static int	put_header(t_config *config, int fd)
{
	char	hdr[54];

	ft_bzero(hdr, 54);
	hdr[0] = 'B';
	hdr[1] = 'M';
	itoc(&hdr[2], config->screen.width * config->screen.height + 54);
	hdr[10] = 54;
	hdr[14] = 40;
	itoc(&hdr[18], config->screen.width);
	itoc(&hdr[22], config->screen.height);
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
			clr = *(unsigned int *)(config->screen.data
					+ (i * config->screen.size_line
						+ j * (config->screen.bits_per_pixel / 8)));
			if (write(fd, &clr, sizeof(clr)) < (ssize_t) sizeof(clr))
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
	fd = open(SCREENSHORT_FILENAME, O_CREAT | O_WRONLY | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
		return (E_OPEN_FILE);
	make_image(config);
	if (put_header(config, fd) || put_image_to_file(config, fd))
		err = E_FILE_WRITE;
	close(fd);
	return (err);
}
