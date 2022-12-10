/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:45:30 by tgriffit          #+#    #+#             */
/*   Updated: 2022/11/29 20:04:18 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	get_map_textures(t_map_data *map, char *first_chars, char *line)
{
	char	*texture;

	if (ft_strncmp(first_chars, "NO ", 3) == 0 \
	|| ft_strncmp(first_chars, "SO ", 3) == 0 \
	|| ft_strncmp(first_chars, "EA ", 3) == 0 \
	|| ft_strncmp(first_chars, "WE ", 3) == 0)
	{
		texture = ft_strchr(line, ' ');
		while (texture && *texture == ' ')
			texture++;
		if (!texture)
			return (0);
		texture = ft_strdup(texture);
		if (ft_strncmp(first_chars, "NO ", 4) == 0 && !map->no_txt)
			map->no_txt = texture;
		else if (ft_strncmp(first_chars, "SO ", 4) == 0 && !map->so_txt)
			map->so_txt = texture;
		else if (ft_strncmp(first_chars, "EA ", 4) == 0 && !map->ea_txt)
			map->ea_txt = texture;
		else if (ft_strncmp(first_chars, "WE ", 4) == 0 && !map->we_txt)
			map->we_txt = texture;
		return (1);
	}
	return (0);
}

char	*get_next_number(char *str)
{
	size_t	i;

	if (!str || ft_strlen(str) < 1)
		return (NULL);
	i = 1;
	while (ft_is_space(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (NULL);
	return (&str[i]);
}

void	get_map_header(int fd, t_map_data *map, t_drawer *drawer)
{
	char	*nl;
	char	*letter;
	size_t	nb_infos;

	nb_infos = 0;
	nl = get_next_line(fd);
	while (nl && nb_infos < 6 && (is_valid_start(nl, drawer)))
	{
		(void)ft_strlcpy(nl, nl, ft_strlen(nl));
		letter = ft_strndup(nl, 3);
		nb_infos += get_map_textures(map, letter, nl);
		if (ft_strncmp(letter, "F ", 2) == 0)
			map->floor_color = split_colors(ft_strdup(get_next_number(nl)));
		else if (ft_strncmp(letter, "C ", 2) == 0)
			map->ceiling_color = split_colors(ft_strdup(get_next_number(nl)));
		nb_infos += (letter && (letter[0] == 'F' || letter[0] == 'C'));
		free(letter);
		free(nl);
		nl = get_next_line(fd);
	}
	free(nl);
}

bool	check_map_header(t_map_data map)
{
	if (!map.no_txt || !map.so_txt)
	{
		printf("Error\nNorth or South texture missing\n");
		return (false);
	}
	if (!map.ea_txt || !map.we_txt)
	{
		printf("Error\nEast or West texture missing\n");
		return (false);
	}
	if (!map.ceiling_color || !map.floor_color \
	|| !are_texturecolors_ok(map.ceiling_color) \
	|| !are_texturecolors_ok(map.floor_color))
	{
		printf("Error\nCeiling or Floor color unavailable\n");
		return (false);
	}
	printf("The header is complete.\n");
	return (true);
}
