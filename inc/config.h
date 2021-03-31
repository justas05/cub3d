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

# define S_EXT ".cub"
# define IMG_WIDTH 64
# define IMG_HEIGHT 64

# define K_ESC 53
# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_UP 126
# define K_DOWN 125
# define K_LEFT 123
# define K_RIGHT 124

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_mlx
{
	void			*ptr;
}					t_mlx;

typedef struct		s_window
{
	void			*ptr;
	t_point			size;
}					t_window;

typedef struct		s_handle
{
	t_mlx			mlx;
	t_window		window;
}					t_handle;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_map
{
	size_t			cols;
	size_t			rows;
	char			**map;
	char			sprite;
}					t_map;

typedef struct		s_config
{
	char			*config_filename;
	unsigned int	*no;
	unsigned int	*so;
	unsigned int	*we;
	unsigned int	*ea;
	unsigned int	*s;
	char			save;
	t_rgb			f;
	t_rgb			c;
	t_map			map;
	t_handle		handle;
}					t_config;

int					parse_config(t_config *config);
void				init_config(t_config *config);
int					init(t_config *config);
void				free_config(t_config *config);
int					extract_texture(t_config *config, char *filename,
									unsigned int **dest);
int					extract_resolution(char *line, t_config *config);
int					extract_sprite_texture(char *line, t_config *config);
int					extract_floor_color(char *line, t_config *config);
int					extract_ceilling_color(char *line, t_config *config);
int					extract_north_texture(char *line, t_config *config);
int					extract_south_texture(char *line, t_config *config);
int					extract_west_texture(char *line, t_config *config);
int					extract_east_texture(char *line, t_config *config);
int					extract_map(int fd, t_config *config);

#endif
