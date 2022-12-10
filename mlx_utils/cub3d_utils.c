/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 12:05:26 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/03 15:06:29 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_clamp_angle(t_drawer *drawer)
{
	while (drawer->player->angle < -M_PI)
		drawer->player->angle += 2.0f * M_PI;
	while (drawer->player->angle > M_PI)
		drawer->player->angle -= 2.0f * M_PI;
}

int	init_win(t_drawer *drawer, char *title)
{
	drawer->mlx = mlx_init();
	if (!drawer->mlx)
		return (-1);
	drawer->window = mlx_new_window(drawer->mlx, WIDTH, HEIGHT, title);
	if (!drawer->window)
		return (-1);
	if (!surface_create(&drawer->main_surf, drawer->mlx, WIDTH, HEIGHT))
		return (1);
	mlx_hook(drawer->window, 2, 0, key_down_hook, drawer);
	mlx_hook(drawer->window, 3, 0, key_up_hook, drawer);
	mlx_hook(drawer->window, 17, 1L << 0, kill_cub3d, drawer);
	mlx_hook(drawer->window, 4, 0, mouse_down, drawer);
	mlx_hook(drawer->window, 5, 0, mouse_up, drawer);
	mlx_hook(drawer->window, 6, 0, mouse_moved, drawer);
	mlx_loop_hook(drawer->mlx, loop_hook, drawer);
	return (0);
}

int	map_load_textures(t_drawer *drawer)
{
	int	i;
	int	rv;

	i = 0;
	rv = load_texture(&drawer->textures[i++], drawer->map->so_txt);
	if (rv >= 0)
		rv = load_texture(&drawer->textures[i++], drawer->map->ea_txt);
	if (rv >= 0)
		rv = load_texture(&drawer->textures[i++], drawer->map->no_txt);
	if (rv >= 0)
		rv = load_texture(&drawer->textures[i++], drawer->map->we_txt);
	if (rv >= 0)
		rv = load_texture(&drawer->textures[i++], "textures/med.tex");
	if (rv >= 0)
		rv = load_texture(&drawer->textures[i++], "textures/gameover.tex");
	if (rv < 0)
	{
		while (i--)
			free_texture(&drawer->textures[i]);
	}
	return (rv);
}

/**
 * Put the pixels into a stamp image, which will be applied by the
 * putpixeltowindow function.
 * @param drawer : Structure which contains the mlx pointers
 * @param x : Coordinate of the pixel
 * @param y : Coordinate of the pixel
 * @param color : See colors.h
 */
void	optimized_pixelput(t_surface *surf, int x, int y, unsigned int color)
{
	unsigned int	*dst;

	if (x < 0 || x >= surf->width || y < 0 || y >= surf->height)
		return ;
	dst = (unsigned int *)(surf->pixels + y * surf->stride);
	dst[x] = color;
}
