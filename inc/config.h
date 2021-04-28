/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbooke <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:08:28 by hbooke            #+#    #+#             */
/*   Updated: 2021/04/28 10:45:06 by hbooke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <stddef.h>

# include <mlx.h>
# include <mlx_int.h>

# define WINDOW_TITLE			"cub3d"
# define SCREENSHORT_FILENAME	"scr.bmp"
# define S_EXT					".cub"
# define IMG_WIDTH				64
# define IMG_HEIGHT				64
# define CROSS_BUTTON			33

enum	e_keys
{
	K_ESC = 65307,
	K_W = 119,
	K_A = 97,
	K_S = 115,
	K_D = 100,
	K_UP = 65362,
	K_DOWN = 65364,
	K_LEFT = 65361,
	K_RIGHT = 65363
};

enum	e_char_codes
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

enum	e_chars
{
	N_ERR = -2,
	N_SPACE,
	N_EMPTY,
	N_WALL,
	N_SPRITE,
	N_NORTH,
	N_SOUTH,
	N_WEST,
	N_EAST,
};

typedef struct s_point_d
{
	double	x;
	double	y;
}			t_point_d;

typedef struct s_point_i
{
	int	x;
	int	y;
}		t_point_i;

typedef struct s_mlx
{
	void	*ptr;
}			t_mlx;

typedef struct s_window
{
	void		*ptr;
	t_point_i	size;
}				t_window;

typedef struct s_handle
{
	t_mlx		mlx;
	t_window	window;
}				t_handle;

typedef struct s_rgb
{
	int	t;
	int	r;
	int	g;
	int	b;
}		t_trgb;

typedef struct s_map_row
{
	char	*cols;
	size_t	col_count;
}			t_map_row;

typedef struct s_map
{
	size_t		row_count;
	t_map_row	*rows;
}				t_map;

typedef struct s_image
{
	void	*addr;
	void	*data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}			t_image;

typedef struct s_player
{
	t_point_d	pos;
	t_point_d	dir;
	double		speed;
}				t_player;

typedef struct s_sprite
{
	t_point_i		pos;
	struct s_sprite	*next;
}					t_sprite;

typedef struct s_draw
{
	t_point_i	map;
	t_point_i	step;
	t_point_d	plane;
	t_point_d	ray;
	t_point_d	delta_dist;
	t_point_d	side_dist;
	t_point_i	range;
	t_sprite	*sprites;
	int			side;
	int			line_h;
	double		p_w_dist;
	int			t_pos;
	double		tex_pos;
	double		wall_dist;
}				t_draw;

typedef struct s_config
{
	char		*config_filename;
	t_player	player;
	t_draw		draw;
	t_image		no;
	t_image		so;
	t_image		we;
	t_image		ea;
	t_image		s;
	t_image		screen;
	t_trgb		f;
	t_trgb		c; 
	t_map		map;
	t_handle	handle;
	char		save;
	double		angle;
}				t_config;

typedef int (*const	t_extract)(char *, t_config *);
typedef int (*		t_action)(t_config *, int);

int		parse_config(t_config *config);
void	init_config(t_config *config);
int		init(t_config *config);
int		extract_texture(t_config *config, char *filename,
			t_image *texture);
int		extract_resolution(char *line, t_config *config);
int		extract_sprite_texture(char *line, t_config *config);
int		extract_floor_color(char *line, t_config *config);
int		extract_ceilling_color(char *line, t_config *config);
int		extract_north_texture(char *line, t_config *config);
int		extract_south_texture(char *line, t_config *config);
int		extract_west_texture(char *line, t_config *config);
int		extract_east_texture(char *line, t_config *config);
int		extract_map(int fd, char *line, t_config *config);
int		check_map(t_config *config);
int		key_handler(int k, void *params);
int		close_handler(t_config *config, int arg);
int		game(t_config *config);
void	main_screen(t_config *config);
int		make_image(t_config *config);
int		make_bmp(t_config *config);
int		add_sprite(t_config *config, ssize_t i, ssize_t j);
void	draw_sprites(t_config *config);
void	clear_sprites(t_config *config);

#endif
