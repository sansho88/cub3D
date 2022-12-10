/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:40:13 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/03 15:57:26 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*split_colors(char *str)
{
	int		*result;
	char	**str_splitted;
	int		i;
	char	*tmp;

	result = ft_calloc(3, sizeof(int *));
	str_splitted = ft_split(str, ',');
	free(str);
	if (!result || !str_splitted)
		exit(28);
	i = -1;
	while (str_splitted[++i])
	{
		if (i < 3)
		{
			tmp = ft_strtrim(str_splitted[i], " ");
			if (!tmp)
				exit(28);
			result[i] = ft_atoi(tmp);
			free(tmp);
		}
		free(str_splitted[i]);
	}
	free(str_splitted);
	return (result);
}

bool	are_texturecolors_ok(int *colors)
{
	size_t	i;

	if (!colors)
		return (false);
	i = 0;
	while (i < 3)
	{
		if (colors[i] < 0 || colors[i] > 255)
		{
			printf("Color unavailable");
			exit(-8);
			return (false);
		}
		i++;
	}
	return (true);
}
