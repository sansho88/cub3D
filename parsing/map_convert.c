/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:16:10 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/03 11:24:33 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_first_mapline(int fd, t_drawer *drawer)
{
	char	*line;
	char	*tmp;

	line = go_to_map(fd, get_next_line(fd));
	tmp = ft_strtrim(line, " ");
	if (!(ft_is_space(tmp[0]) || ft_isdigit(tmp[0])))
	{
		free(line);
		kill_cub3d(drawer, "Error\nWrong infos in the map file.");
	}
	free(tmp);
	while (line)
	{
		tmp = ft_strtrim(line, " ");
		if (tmp && ft_isdigit(tmp[0]))
			break ;
		free(line);
		free(tmp);
		tmp = NULL;
		line = get_next_line(fd);
	}
	if (tmp)
		free(tmp);
	return (line);
}

/**
 * Used essentially for delimit the parsing at the init.
 * @param fd
 * @param xmax :Address of the int which will receives the number of colomns
 * @param ymax :Address of the int which will receives the number of lines
 */
void	getmapxymax(int fd, t_map_data *map)
{
	char	*s;
	int		i;

	if (fd < 0)
		return ;
	map->ymax = 0;
	s = get_next_line(fd);
	while (s)
	{
		if (ft_strlen(s) > 1)
		{
			(map->ymax)++;
			i = -1;
			while (s[++i])
				if (i > (int)map->xmax)
					map->xmax = i;
		}
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close (fd);
}

char	**get_map(int fd, t_map_data *map_data, t_drawer *drawer)
{
	char	**result;
	char	*line;
	size_t	y;

	result = ft_calloc(map_data->ymax + 1, sizeof(char **));
	line = get_first_mapline(fd, drawer);
	y = 0;
	while (line && y < map_data->ymax)
	{
		if (ft_strlen(line) > 1)
		{
			result[y] = ft_calloc(map_data->xmax + 2, sizeof(char));
			ft_strlcpy(result[y], line, map_data->xmax + 2 - \
				(y == map_data->ymax));
				y++;
		}
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	free(line);
	result[y] = NULL;
	return (result);
}

static float	angle_from_cardinal(int cardinal)
{
	if (cardinal == 'E')
		return (M_PI_2);
	else if (cardinal == 'S')
		return (0.0f);
	else if (cardinal == 'W')
		return (-M_PI_2);
	return (M_PI);
}

void	convert_map(t_drawer *d, t_map_data	*map)
{
	size_t	x;
	size_t	y;
	char	digit;

	y = 0;
	map->map = ft_calloc(map->ymax + 1, sizeof(int *));
	while (y < map->ymax)
	{
		x = 0;
		map->map[y] = ft_calloc(map->xmax, sizeof(int));
		while (x < map->xmax)
		{
			digit = map->str_map[y][x];
			if (digit == 'N' || digit == 'S' || digit == 'W' || digit == 'E')
			{
				map->player->x = x - 0.5f;
				map->player->y = y + 0.5f;
				map->player->start_angle = angle_from_cardinal(digit);
			}
			if (digit == 'M')
				spawn_medpack(d, x + 0.5f, y + 0.5f);
			map->map[y][x++] = ft_atoi(&digit);
		}
		y++;
	}
}
