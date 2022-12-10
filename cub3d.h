/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:08:29 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/02 18:52:06 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "minilibx_macos/mlx.h"
# include "get_next_line/get_next_line_bonus.h"
# include "libft/libft.h"
# include "colors.h"
# include "controls/keys.h"
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>

# define WIDTH 1300
# define HEIGHT 1200
# define FOV 120
# ifndef OFFSET
#  define OFFSET 10.0f
# endif
# define X 0
# define Y 1
# define CELL_SIZE 40
# define VIEW_DIST 800
# define MINIMAP_WIDTH 300
# define MINIMAP_HEIGHT 300
# define MINIMAP_ZOOM 20

# define MAX_KEYS 16

# define ACTION_LEFT 0
# define ACTION_RIGHT 1
# define ACTION_FORWARD 2
# define ACTION_BACKWARD 3
# define ACTION_STRAFE_LEFT 4
# define ACTION_STRAFE_RIGHT 5

# define MOVE_SPEED 0.1f

# define MAX_SPRITES 8

# define MAX_LOOK_PITCH 100.0f

/////////////////////////// STRUCTS ///////////////////////////////////////////

typedef struct s_player {
	float	x;
	float	y;
	float	angle;
	float	start_angle;
}t_player;

typedef struct s_minimap
{
	void	*image;
	int		width;
	int		height;
	int		x;
	int		y;
}	t_minimap;

typedef struct s_input
{
	int	key_bindings[MAX_KEYS];
	int	key_states[MAX_KEYS];
}	t_input;

typedef struct s_map {
	int				**map;
	int				fd_map;
	size_t			xmax;
	size_t			ymax;
	char			*name;
	char			**str_map;
	char			*no_txt;
	char			*so_txt;
	char			*we_txt;
	char			*ea_txt;
	int				*floor_color;
	int				*ceiling_color;
	t_player		*player;
}	t_map_data;

typedef struct s_scissor
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_scissor;

typedef struct s_line_ctx
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_line_ctx;

typedef struct s_surface
{
	int				endian;
	int				bpp;
	int				stride;
	void			*img;
	unsigned char	*pixels;
	unsigned short	width;
	unsigned short	height;
}	t_surface;

typedef struct s_painter
{
	int				ypen;
	int				xpen;
	unsigned int	colpen;
	float			mat[4];
	int				xtrans;
	int				ytrans;
	t_surface		*surf;
	t_scissor		scissor;
}	t_painter;

/**
 * Structure for the Digital Differential Analyzer function (dda()). \n
 * Only composed of array[2], where: \n
 * '[0]' = x \n
 * '[1]' = y \n
 */
typedef struct s_dda {
	float	origin[2];
	float	pos[2];
	float	side_dist[2];
	float	delta_dist[2];
	int		side;
	float	dist;
	float	target[2];
	float	wall_x;
}	t_dda;

typedef struct s_texture
{
	unsigned char	*pixels;
	int				width;
	int				height;
	int				pitch;
}	t_texture;

typedef struct s_sprite
{
	int			enabled;
	float		x;
	float		y;
	float		y_size;
	float		x_size;
	float		hsize;
	float		wsize;
	t_texture	*tex;
	float		xscreen;
	float		yscreen;
	float		scale;
	float		depth;
	int			xmax;
	int			xmin;
	int			ymin;
	int			ymax;
	int			xstop;
	int			ystop;
}	t_sprite;

typedef struct s_drawer {
	void			*mlx;
	void			*window;
	t_surface		main_surf;
	t_surface		minimap_surf;

	t_map_data		*map;
	t_minimap		minimap;
	t_player		*player;
	t_dda			*dda;

	t_texture		textures[6];
	t_input			input;

	int				grab_x;
	int				grab_y;
	int				is_grabbing;

	unsigned int	floorcol;
	unsigned int	ceilcol;

	float			tan_half_fov;
	float			half_fov;

	float			dir_x;
	float			dir_y;

	float			plane_x;
	float			plane_y;

	t_sprite		sprites[MAX_SPRITES];
	int				nsprites;

	int				health;
	int				anim_health;
	int				dmg_ticks;

	float			look_pitch;

	int				dda_mode;
}	t_drawer;

/////////////////////////// FUNCTIONS /////////////////////////////////////////

///////////////// PARSING ///////////////////////
// [map_header.c]
void		get_map_header(int fd, t_map_data *map, t_drawer *drawer);
bool		check_map_header(t_map_data map);

// [map_parsing.c]
bool		is_filename_ok(char *name, char *ext);
char		*go_to_map(int fd, char *start_line);
bool		is_valid_start(char *str, t_drawer *drawer);

// [map_convert.c]
char		**get_map(int fd, t_map_data *map_data, t_drawer *drawer);
void		convert_map(t_drawer *d, t_map_data	*map);

// [colors_header.c]
int			*split_colors(char *str);
bool		are_texturecolors_ok(int *colors);

// [cub3d_utils.c]
void		parse_map(int fd, t_map_data *map, t_drawer *drawer);
void		getmapxymax(int fd, t_map_data *map);
void		optimized_pixelput(t_surface *surf, int x, int y, \
															unsigned int color);
int			map_load_textures(t_drawer *drawer);
int			init_win(t_drawer *drawer, char *title);

// [minimap.c]
void		minimap_init(t_drawer *d);

// [map_enclosed.c]
bool		is_player_enclosed(t_map_data *map, int x, int y);

//////////////// EXEC ////////////////////////
// [keys.c]
int			kill_cub3d(t_drawer *drawer, char const *msg);
int			key_up_hook(int keycode, t_drawer *drawer);
int			key_down_hook(int keycode, t_drawer *drawer);
void		init_keyboard(t_input *input);

// [dda.c]
void		dda(t_drawer *drawer, t_dda *dda, float *dir);

// [render.c]
void		render_frame(t_drawer *drawer);
void		line_to(t_painter *painter, int x, int y);
void		move_to(t_painter *painter, int x, int y);

// [compass.c]
void		draw_compass(t_drawer *drawer, t_minimap *minimap);

// [image.c]

/**
 * @brief Loads a texture from file into tex.
 * 
 * @param tex The texture object containing the image data
 * @param file The from from which the image is loaded.
 * @return int Negative values indicate erros
 */
int			load_texture(t_texture *tex, const char *file);

/**
 * @brief Frees the textures data from memory
 * 
 * @param tex 
 */
void		free_texture(t_texture *tex);

void		player_clamp_angle(t_drawer *drawer);
void		process_inputs(t_drawer *drawer);
void		dir_from_inputs(t_input *input, float dir[2], float c, float s);

int			surface_create(
				t_surface *surf, void *mlx,
				unsigned short width, unsigned short height);

void		minimap_render(t_drawer *drawer, t_painter *painter);
void		painter_create(t_painter *painter, t_surface *surf);
void		set_rotation(t_painter *painter, float ang);
void		set_origin(t_painter *painter, int x, int y);

// [minimap_icons_bonus.c]
void		draw_icons(t_drawer *drawer, t_painter *painter);

// [hooks.c]
int			loop_hook(void *param);
int			mouse_down(int button, int x, int y, t_drawer *drawer);
int			mouse_moved(int x, int y, t_drawer *drawer);
int			mouse_up(int button, int x, int y, t_drawer *drawer);
void		draw_stripe(t_drawer *drawer, int x, int h, t_dda *dda);
void		set_field_of_view(t_drawer *drawer, float fov);

// [sprite.c]
void		spawn_medpack(t_drawer *drawer, float x, float y);
void		render_sprites(t_drawer *drawer, int const *indices, float *depth);

// [sprite_sort.c]
void		sort_sprites(t_drawer *d, int *ids);

// [painter.c]
void		painter_clear(t_painter *painter, unsigned int color);
void		transform_point(t_painter *painter, int x, int y, int *out);
void		set_identity(t_painter *painter);

// [lifebar.c]
void		draw_lifebar(t_drawer *drawer, t_surface *surf);

// [gameover.c]
void		draw_gameover(t_surface *surf, t_texture const *tex);

// 
void		snd_play(const char *path);

// [doors_bonus.c]
void		spawn_door(t_drawer *drawer);

#endif
