/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:46:50 by alavaud           #+#    #+#             */
/*   Updated: 2022/11/23 19:53:02 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	update_lifebar(t_drawer *drawer)
{
	if (drawer->dmg_ticks == 0)
	{
		if (drawer->health > drawer->anim_health)
			++drawer->anim_health;
		if (drawer->health < drawer->anim_health)
			--drawer->anim_health;
	}
	if (drawer->dmg_ticks > 0)
		--drawer->dmg_ticks;
}

static unsigned int	lifebar_pixel_col(t_drawer *drawer, int x, int y)
{
	int	cur;

	if (y >= 40)
		return (0);
	if (x < 40)
	{
		if (x >= 16 && x <= 24 && y >= 8 && y <= 32)
			return (0x00ffffff);
		else if (x >= 8 && x <= 32 && y >= 16 && y <= 24)
			return (0x00ffffff);
		return (0x00d0d0d0);
	}
	else
	{
		cur = (x - 40) * 40 / 260;
		if (cur < drawer->anim_health && drawer->dmg_ticks > 8)
			return (0x00ff0000);
		else if (cur < drawer->health)
			return (0x0000ff00);
		else if (cur < drawer->anim_health)
			return (0x00008000);
		return (0x00505050);
	}
	return (0);
}

void	draw_lifebar(t_drawer *drawer, t_surface *surf)
{
	unsigned int	c;
	int				x;
	int				y;

	y = 0;
	while (y < 44)
	{
		x = 0;
		while (x < 300)
		{
			c = lifebar_pixel_col(drawer, x, y);
			optimized_pixelput(surf, 10 + x, HEIGHT - 54 + y, c);
			++x;
		}
		++y;
	}
	update_lifebar(drawer);
}
