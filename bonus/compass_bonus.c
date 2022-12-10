/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:26:47 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/02 15:26:23 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define COMPASS_SPACING 100

static void	draw_str_centered(t_drawer *drawer, int x, int y,
	const char *s)
{
	int	i;
	int	width;

	i = 0;
	while (s[i])
		++i;
	width = i * 5;
	mlx_string_put(drawer->mlx, drawer->window,
		x - width, y, 0x00ffffff, (char *)s);
}

void	draw_compass(t_drawer *drawer, t_minimap *minimap)
{
	const char	*pos[] = {"S", "SW", "W", "NW", "N", "NE", "E", "SE",};
	int			offset;
	int			i;
	int			xpos;

	offset = minimap->width / 2
		+ (drawer->player->angle / M_PI_4) * COMPASS_SPACING;
	i = 0;
	while (i < 8)
	{
		xpos = i * COMPASS_SPACING + offset;
		if (xpos > 8 * COMPASS_SPACING)
			xpos -= 8 * COMPASS_SPACING;
		if (xpos >= 0)
			draw_str_centered(drawer,
				minimap->x + xpos, minimap->y + 20, pos[i]);
		++i;
	}
}
