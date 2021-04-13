/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2020/11/22 21:08:28 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <stddef.h>

# include <mlx.h>
# include <mlx_int.h>

# define S_EXT		".cub"
# define IMG_WIDTH	64
# define IMG_HEIGHT	64

enum	e_keys
{
	K_ESC = 53,
	K_W = 13,
	K_A = 0,
	K_S = 1,
	K_D = 2,
	K_UP = 126,
	K_DOWN = 125,
	K_LEFT = 123,
	K_RIGHT = 124
};

enum	e_chars
{
	C_SPACE = ' ',
	C_EMPTY = '0',
	C_WALL = '1',
	C_SPRITE = '2',
	C_NORTH = 'N',
	C_SOUTH = 'S',
	C_WEST = 'W',
	C_EAST = 'E'
};

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_mlx
{
	void	*ptr;
}			t_mlx;

typedef struct s_window
{
	void	*ptr;
	t_point	size;
}			t_window;

typedef struct s_handle
{
	t_mlx		mlx;
	t_window	window;
}				t_handle;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_map_row
{
	char	*cols;
	size_t	col_count;
}			t_map_row;

typedef struct s_map
{
	size_t		row_count;
	t_map_row	*rows;
	char		sprite;
}				t_map;

typedef struct s_texture
{
	void	*addr;
	void	*data;
}			t_texture;

typedef struct s_config
{
	char		*config_filename;
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	t_texture	s;
	char		save;
	t_rgb		f;
	t_rgb		c;
	t_map		map;
	t_handle	handle;
}				t_config;

int				parse_config(t_config *config);
void			init_config(t_config *config);
int				init(t_config *config);
int				extract_texture(t_config *config, char *filename,
					t_texture *texture);
int				extract_resolution(char *line, t_config *config);
int				extract_sprite_texture(char *line, t_config *config);
int				extract_floor_color(char *line, t_config *config);
int				extract_ceilling_color(char *line, t_config *config);
int				extract_north_texture(char *line, t_config *config);
int				extract_south_texture(char *line, t_config *config);
int				extract_west_texture(char *line, t_config *config);
int				extract_east_texture(char *line, t_config *config);
int				extract_map(int fd, char *line, t_config *config);

#endif
