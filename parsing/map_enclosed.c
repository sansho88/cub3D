/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_enclosed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 10:56:59 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/03 14:49:37 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_out_of_bounds(t_map_data *map, int x, int y)
{
	return (x > (int)map->xmax - 1 || x < 0 || y > (int)map->ymax - 1 || y < 0);
}

bool	is_player(char digit)
{
	return (digit == 'N' || digit == 'S' || digit == 'W' || digit == 'E');
}

bool	is_player_enclosed(t_map_data *map, int x, int y)
{
	if (!is_out_of_bounds(map, x, y))
	{
		if (!map->str_map[y][x])
			exit(-8);
		if (map->str_map[y][x] == '1')
			return (true);
		if (map->str_map[y][x] == '0' || map->str_map[y][x] == ' ' \
		|| map->str_map[y][x] == '\n' || map->str_map[y][x] == 'M'
		|| is_player(map->str_map[y][x]))
		{
			map->str_map[y][x] = '1';
			return (is_player_enclosed(map, x + 1, y) \
					+ is_player_enclosed(map, x, y + 1) \
					+ is_player_enclosed(map, x - 1, y) \
					+ is_player_enclosed(map, x, y - 1));
		}
		return (true);
	}
	else
	{
		printf("The player can escape from the map (x:%d, y:%d).\n", x, y);
		exit(-8);
	}
}
