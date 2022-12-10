/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_icons_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:22:51 by alavaud           #+#    #+#             */
/*   Updated: 2022/12/02 15:23:58 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_health_icon(t_surface *surf,
	int xpos, int ypos, unsigned int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < 16)
	{
		x = 0;
		while (x < 16)
		{
			if ((y >= 6 && y < 10) || (x >= 6 && x < 10))
				optimized_pixelput(surf, xpos + x, ypos + y, color);
			++x;
		}
		++y;
	}
}

static void	draw_health_icons(t_drawer *drawer,
	t_painter *painter, unsigned int color)
{
	t_sprite	*sprite;
	int			out[2];
	int			i;

	i = 0;
	while (i < drawer->nsprites)
	{
		sprite = &drawer->sprites[i];
		if (sprite->enabled)
		{
			transform_point(painter,
				(drawer->player->x - sprite->x) * MINIMAP_ZOOM,
				(drawer->player->y - sprite->y) * MINIMAP_ZOOM,
				out);
			draw_health_icon(painter->surf,
				out[0] - 8,
				out[1] - 8, color);
		}
		++i;
	}
}

void	draw_icons(t_drawer *drawer, t_painter *painter)
{
	static int		fade = 0;
	unsigned int	color;

	++fade;
	if (fade >= 40)
		fade = 0;
	if (fade >= 20)
		color = (400 - fade) * 127 / 20;
	else
		color = fade * 127 / 20;
	draw_health_icons(drawer, painter, (color + 128) << 16);
}
