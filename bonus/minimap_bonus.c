/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:22:51 by alavaud           #+#    #+#             */
/*   Updated: 2022/12/02 19:10:33 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	minimap_init(t_drawer *d)
{
	d->minimap.x = WIDTH - MINIMAP_WIDTH - 10;
	d->minimap.y = 10;
	d->minimap.width = MINIMAP_WIDTH;
	d->minimap.height = MINIMAP_HEIGHT;
	d->minimap_surf.pixels = d->main_surf.pixels \
	+ d->minimap.x * 4 + d->minimap.y * d->main_surf.stride;
	d->minimap_surf.width = MINIMAP_WIDTH;
	d->minimap_surf.height = MINIMAP_HEIGHT;
	d->minimap_surf.stride = d->main_surf.stride;
}

void	draw_player_icon(t_painter *painter)
{
	painter->colpen = RGB_CYAN;
	set_identity(painter);
	move_to(painter, 0, 0);
	line_to(painter, 0 + 8, 0 + 8);
	line_to(painter, 0, 0 - 16);
	line_to(painter, 0 - 8, 0 + 8);
	line_to(painter, 0, 0);
}

static void	draw_cell(t_painter *painter, int x, int y)
{
	int	i;

	painter->colpen = RGB_GREEN;
	i = 0;
	while (i < MINIMAP_ZOOM)
	{
		move_to(painter, x, y - i);
		line_to(painter, x + MINIMAP_ZOOM, y - i);
		++i;
	}
}

static void	draw_overlay(t_surface *surf)
{
	unsigned int	*row;
	int				y;
	int				x;

	y = 0;
	while (y < surf->height)
	{
		x = 0;
		row = (unsigned int *)(surf->pixels + y * surf->stride);
		while (x < surf->width)
		{
			row[x] = (row[x] >> 1) & 0x007f7f7f;
			++x;
		}
		y += 3;
	}
}

void	minimap_render(t_drawer *drawer, t_painter *painter)
{
	const t_player	*player = drawer->player;
	int				i;
	int				j;

	painter_clear(painter, 0x00104000);
	set_rotation(painter, player->angle);
	set_origin(painter, MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2);
	painter->colpen = RGB_GREEN;
	i = 0;
	while (i < (int)drawer->map->ymax)
	{
		j = 0;
		while (j < (int)drawer->map->xmax)
		{
			if (drawer->map->map[i][j] && drawer->map->map[i][j] != 3)
				draw_cell(painter,
					(player->x - j - 1) * MINIMAP_ZOOM,
					(player->y - i) * MINIMAP_ZOOM);
			++j;
		}
		++i;
	}
	draw_icons(drawer, painter);
	draw_player_icon(painter);
	draw_overlay(painter->surf);
}
