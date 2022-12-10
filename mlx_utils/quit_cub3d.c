/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:37:33 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/01 15:17:47 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "../cub3d.h"

void	free_int_tabs(int **tab, size_t size)
{
	size_t	i;

	i = 0;
	if (tab && *tab)
		while (i < size)
			free(tab[i++]);
	free(tab);
}

void	free_char_tabs(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			free(tab[i++]);
	free(tab);
	tab = NULL;
}

void	free_drawer_map(t_map_data *map)
{
	free_int_tabs(map->map, map->ymax);
	if (map->str_map)
		free_char_tabs(map->str_map);
	free(map->no_txt);
	free(map->so_txt);
	free(map->we_txt);
	free(map->ea_txt);
	free(map->floor_color);
	free(map->ceiling_color);
	close(map->fd_map);
}

int	kill_cub3d(t_drawer *drawer, char const *msg)
{
	int	i;

	if (msg)
		ft_putendl_fd((char *)msg, 2);
	else
		ft_putendl_fd("Cub3D has exit without error. Have a nice day!", 2);
	i = 0;
	while (i < 6)
		free_texture(drawer->textures + i++);
	if (drawer->main_surf.img)
		mlx_destroy_image(drawer->mlx, drawer->main_surf.img);
	if (drawer->window)
		mlx_destroy_window(drawer->mlx, drawer->window);
	free(drawer->player);
	free(drawer->dda);
	free_drawer_map(drawer->map);
	exit(0);
}
