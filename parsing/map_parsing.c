/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:53:08 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/03 11:12:32 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_filename_ok(char *name, char *ext)
{
	bool		is_map_ok;
	int			fd;
	const char	*file_ext = ft_strrchr(name, '.');

	if (!file_ext)
		return (false);
	is_map_ok = ft_strncmp(file_ext, ext, 4) == 0;
	if (!is_map_ok)
		printf("\'%s\' has to be in the %s format.\n", name, ext);
	fd = open(name, O_RDONLY);
	if (fd < 1)
	{
		is_map_ok = false;
		printf("\'%s\' not found\n", name);
	}
	return (is_map_ok);
}

__attribute__((weak))
bool	is_parsedmap_ok(char **map, t_drawer *drawer)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!map || !*map)
		kill_cub3d(drawer, "There's no map in this file.");
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		while (map[i][j])
		{
			if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' \
			&& map[i][j] != 'W' && map[i][j] != '\n' && !(map[i][j] >= '0' \
			&& map[i][j] <= '1') && map[i][j] != 'M' && !ft_is_space(map[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

/**
 * Copy the map.fdf into a double-array of integers
 * @param fd : The FileDescriptor of the map available for reading.
 * @param xmax
 * @param ymax
 * @return The map parsed formatted in map[y][x]
 */
void	parse_map(int fd, t_map_data *map, t_drawer *drawer)
{
	get_map_header(fd, map, drawer);
	map->fd_map = open(map->name, O_RDONLY);
	if (map->fd_map < 0)
		kill_cub3d(drawer, "Error\nThe file's map can't be read.");
	if (!check_map_header(*map))
		kill_cub3d(drawer, NULL);
	printf("Calculating the map size....\n");
	getmapxymax(fd, map);
	map->str_map = get_map(map->fd_map, map, drawer);
	if (!is_parsedmap_ok(map->str_map, drawer))
		kill_cub3d(drawer, "There is at least 1 invalid character in the map.");
	convert_map(drawer, map);
	drawer->player->x = drawer->map->player->x + 1;
	drawer->player->y = drawer->map->player->y;
	if (is_player_enclosed(map, drawer->player->x, drawer->player->y))
		printf("The player is enclosed.\n");
}

char	*go_to_map(int fd, char *start_line)
{
	char	*tmp;
	char	*line;
	size_t	nb_infos;

	nb_infos = 0;
	tmp = ft_strtrim(start_line, " ");
	line = ft_strdup(start_line);
	free(start_line);
	while (ft_strlen(tmp) && !(ft_isdigit(tmp[0])))
	{
		nb_infos += (!ft_isdigit(tmp[0]) && !ft_is_space(tmp[0]));
		free(line);
		free(tmp);
		line = get_next_line(fd);
		tmp = ft_strtrim(line, " ");
		if (nb_infos >= 6 && !ft_isdigit(tmp[0]) && !ft_is_space(tmp[0]))
			break ;
	}
	free(tmp);
	return (line);
}

bool	is_valid_start(char *str, t_drawer *drawer)
{
	char	start[4];

	if (str && ft_strlen(str) < 3)
		return (true);
	ft_strlcpy(start, str, 4);
	if (ft_is_space(start[0]))
		return (true);
	if (ft_isdigit(start[0]))
		return (false);
	if (!ft_strncmp(start, "NO ", 3) || !ft_strncmp(start, "SO ", 3) \
	|| !ft_strncmp(start, "WE ", 3) || !ft_strncmp(start, "EA ", 3) \
	|| !ft_strncmp(start, "F ", 2) || !ft_strncmp(start, "C ", 2))
	{
		return (true);
	}
	kill_cub3d(drawer, "Error\nIncorrect informations in the header.");
	return (false);
}
