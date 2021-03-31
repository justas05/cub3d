/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errors.h>
#include <config.h>
#include <check.h>

/*
#define BYTE_BITS 8

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

void			my_mlx_pixel_put(t_data *data, t_point *p, int color)
{
	char	*dst;

	dst = data->addr + (p->y * data->line_length + p->x * (data->bits_per_pixel / BYTE_BITS));
	*(unsigned int*)dst = color;
}

void			my_mlx_line_put(t_data *data, t_point *p1, t_point *p2, int color)
{
	int		mn;
	int		mx;
	t_point	cur;
	// y = (y2 - y1) * (x - x1) / (x2 - x1) + y1;

	mn = p1->x;
	mx = p2->x;
	if (p1->x > p2->x)
	{
		mn = p2->x;
		mx = p1->x;
	}
	while (mn <= mx)
	{
		cur.x = mn;
		cur.y = (p2->y - p1->y) * (mn - p1->x) / (p2->x - p1->x) + p1->y;
		my_mlx_pixel_put(data, &cur, color);
		++mn;
	}
}

int				key_hook(int keycode, t_handle *vars)
{
	printf("Hello from key_hook - %d!\n", keycode);
	return (0);
}

int				close_win(int keycode, t_handle *handle)
{
	mlx_destroy_window(handle->mlx, handle->win);
	return (0);
}

int				mouse_hook(t_handle *vars)
{
	t_xvar xvar;
	t_point p;
	
	mlx_int_get_visual(&xvar);
	mlx_mouse_get_pos(&xvar, vars->win, &p.x, &p.y);
	printf("%d %d\n", p.x, p.y);
	return (0);
}

void test()
{
	t_handle	handle;
	t_data		img;
	t_point		size;
	t_point		p1;
	t_point		p2;

	size.x = 720;
	size.y = 840;

	p1.x = 0;
	p1.y = 0;
	p2.x = 700;
	p2.y = 700;
	handle.mlx = mlx_init();
	handle.win = mlx_new_window(handle.mlx, size.x, size.y, "Hello world!");
	img.img = mlx_new_image(handle.mlx, size.x, size.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									&img.endian);
	my_mlx_line_put(&img, &p1, &p2, 0x00FF0000);
	mlx_key_hook(handle.win, key_hook, &handle);
	mlx_hook(handle.win, 2, 1L<<0, close_win, &handle);
	mlx_mouse_hook(handle.win, mouse_hook, &handle);
	mlx_put_image_to_window(handle.mlx, handle.win, img.img, 0, 0);
	mlx_loop(handle.mlx);
}*/


/*
int main()
{
	t_handle s = { .window.size.x = 700, .window.size.y = 700 };

	s.mlx.ptr = mlx_init();
	s.window.ptr = mlx_new_window(s.mlx.ptr, s.window.size.x, s.window.size.y, "cub3D");

	int		bpp;
	int		sl;
	int		end;
	int		tab[5];

	void *img = mlx_xpm_file_to_image(s.mlx.ptr, "/home/makar/projects/school42/cub3d/rcs/aprwx-sl3jj.xpm", &tab[0], &tab[1]);
	printf("%p\n", img);
	//int *adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	//free(img);

	// img = mlx_new_image(s.mlx.ptr, s.window.size.x, s.window.size.y);
	// s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &bpp, &sl, &end);
	mlx_put_image_to_window(s.mlx.ptr, s.window.ptr, img, 0, 0);
	getchar();
	return 0;
}*/

int				main(int argc, char **argv)
{
	t_config	config;
	int			err;

	err = 0;
	init_config(&config);
	config.handle.mlx.ptr = mlx_init();
	if (check_args(argc, argv, &config) < 0 ||
		parse_config(&config) < 0 ||
		init(&config) < 0)
	{
		err = -1;
	}
	free_config(&config);
	return (err);
}
