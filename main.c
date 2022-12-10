/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:07:10 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/02 16:04:08 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_structs(t_drawer *drawer, char *map_name)
{
	if (init_win(drawer, map_name) < 0)
		return (-1);
	drawer->map = ft_calloc(sizeof(t_map_data), 1);
	if (!drawer->map)
		return (-1);
	drawer->player = ft_calloc(1, sizeof(t_player));
	if (!drawer->player)
		return (-1);
	drawer->map->player = drawer->player;
	drawer->dda = ft_calloc(1, sizeof(t_dda));
	if (!drawer->dda)
		return (-1);
	drawer->dda_mode = 2;
	init_keyboard(&drawer->input);
	return (0);
}

static unsigned int	make_color(int *col)
{
	return (col[0] << 16 | col[1] << 8 | col[2]);
}

int	steam_launch_cub3d(t_drawer *drawer, char *path)
{
	int	fd;

	if (init_structs(drawer, path) < 0)
	{
		kill_cub3d(drawer, "Error\nCould not initialize cub3d\n");
		return (1);
	}
	minimap_init(drawer);
	fd = open(path, O_RDONLY);
	drawer->map->name = path;
	parse_map(fd, drawer->map, drawer);
	if (map_load_textures(drawer) < 0)
	{
		kill_cub3d(drawer, "Error\nAt least one texture isn't available.\n");
		return (1);
	}
	drawer->player->angle = drawer->map->player->start_angle;
	drawer->health = 3;
	drawer->anim_health = 3;
	drawer->floorcol = make_color(drawer->map->floor_color);
	drawer->ceilcol = make_color(drawer->map->ceiling_color);
	set_field_of_view(drawer, FOV);
	mlx_loop(drawer->mlx);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_drawer	drawer;

	ft_bzero(&drawer, sizeof(drawer));
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" <map.cub>\n", 2);
		return (1);
	}
	if (!is_filename_ok(argv[1], ".cub"))
	{
		ft_putstr_fd("Invalid map name : ", 2);
		ft_putendl_fd(argv[1], 2);
		return (1);
	}
	return (steam_launch_cub3d(&drawer, argv[1]));
}
