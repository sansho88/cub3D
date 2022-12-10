/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:26:40 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/02 17:29:44 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	spawn_door(t_drawer *drawer)
{
	t_player	*player;
	int			pos[2];
	float		dir[2];
	t_dda		*da;

	player = drawer->player;
	da = drawer->dda;
	pos[Y] = (int)player->y;
	pos[X] = (int)player->x;
	dir[X] = sin(drawer->player->angle);
	dir[Y] = cos(drawer->player->angle);
	dir_from_inputs(&drawer->input, dir, cos(drawer->player->angle), \
	sin(drawer->player->angle));
	drawer->dda_mode = 16;
	dda(drawer, drawer->dda, dir);
	if (da->dist < 2.0f)
	{
		if (drawer->map->map[(int) da->pos[Y]][(int)(da->pos[X])] == 3)
			drawer->map->map[(int) da->pos[Y]][(int)(da->pos[X])] = 2;
		else if (drawer->map->map[(int) da->pos[Y]][(int)(da->pos[X])] == 2)
			drawer->map->map[(int) da->pos[Y]][(int)(da->pos[X])] = 3;
	}
	drawer->dda_mode = 2;
}

static int	find_action_index(t_input *input, int scancode)
{
	int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		if (input->key_bindings[i] == scancode)
			return (i);
		++i;
	}
	return (-1);
}

int	key_down_hook(int keycode, t_drawer *drawer)
{
	t_input	*input;
	int		action;

	if (keycode == KEY_ESC)
		kill_cub3d(drawer, NULL);
	input = &drawer->input;
	action = find_action_index(input, keycode);
	if (keycode == KEY_P)
	{
		drawer->dmg_ticks = 12;
		if (drawer->health > 1)
		{
			drawer->health -= 10;
			if (drawer->health < 0)
				drawer->health = 0;
			snd_play(&"hurt2.wav\0hurt3.mp3"[10 * (rand() & 1)]);
		}
	}
	if (keycode == KEY_R)
		spawn_door(drawer);
	if (action >= 0)
		input->key_states[action] = 1;
	return (0);
}

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
		while (ft_is_space(map[i][j]))
			j++;
		while (map[i][j])
		{
			if (map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' \
			&& map[i][j] != 'W' && map[i][j] != '\n' && !(map[i][j] >= '0' \
			&& map[i][j] <= '3') && map[i][j] != 'M' && !ft_is_space(map[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
