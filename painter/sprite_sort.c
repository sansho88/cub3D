/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:34:51 by alavaud           #+#    #+#             */
/*   Updated: 2022/12/01 15:40:36 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static float	get_dist_squared(t_player *p, t_sprite *s)
{
	float	delta_x;
	float	delta_y;

	delta_x = p->x - s->x;
	delta_y = p->y - s->y;
	return (delta_x * delta_x + delta_y * delta_y);
}

static int	compare_sprites(t_drawer *d, t_sprite *a, t_sprite *b)
{
	return (get_dist_squared(d->player, a) < get_dist_squared(d->player, b));
}

static void	set_indices(int *ids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ids[i] = i;
		++i;
	}
}

void	sort_sprites(t_drawer *d, int *ids)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	set_indices(ids, d->nsprites);
	while (i < d->nsprites)
	{
		j = i + 1;
		while (j < d->nsprites)
		{
			if (compare_sprites(d, d->sprites + ids[i], d->sprites + ids[j]))
			{
				tmp = ids[i];
				ids[i] = ids[j];
				ids[j] = tmp;
			}
			++j;
		}
		++i;
	}
}
