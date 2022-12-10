/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:39:44 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/02 15:16:10 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_player_manager(t_input *input, t_player *player, t_drawer *draw)
{
	if (draw->is_grabbing)
		return ;
	if (input->key_states[ACTION_LEFT])
	{
		player->angle += 0.1f;
		player_clamp_angle(draw);
	}
	else if (input->key_states[ACTION_RIGHT])
	{
		player->angle -= 0.1f;
		player_clamp_angle(draw);
	}
}

void	move_player(t_drawer *drawer, float dir_x, float dir_y)
{
	t_dda	da[2];
	float	dir[2];

	dir[Y] = 0.0f;
	dir[X] = -1.0f;
	if (dir_x > 0)
		dir[X] = 1.0f;
	dda(drawer, &da[X], dir);
	if (da[X].dist >= 0.22f)
		drawer->player->x += dir_x * MOVE_SPEED;
	dir[X] = 0.0f;
	dir[Y] = -1.0f;
	if (dir_y > 0)
		dir[Y] = 1.0f;
	dda(drawer, &da[Y], dir);
	if (da[Y].dist >= 0.22f)
		drawer->player->y += dir_y * MOVE_SPEED;
}

void	dir_from_inputs(t_input *input, float dir[2], float c, float s)
{
	if (input->key_states[ACTION_FORWARD]
		&& !input->key_states[ACTION_BACKWARD])
	{
		dir[X] = s;
		dir[Y] = c;
	}
	if (input->key_states[ACTION_BACKWARD]
		&& !input->key_states[ACTION_FORWARD])
	{
		dir[X] = -s;
		dir[Y] = -c;
	}
	if (input->key_states[ACTION_STRAFE_RIGHT]
		&& !input->key_states[ACTION_STRAFE_LEFT])
	{
		dir[X] -= c;
		dir[Y] += s;
	}
	if (input->key_states[ACTION_STRAFE_LEFT]
		&& !input->key_states[ACTION_STRAFE_RIGHT])
	{
		dir[X] += c;
		dir[Y] -= s;
	}
}

void	process_inputs(t_drawer *drawer)
{
	t_input		*input;
	float		dir[2];
	float		len;

	input = &drawer->input;
	dir[X] = 0.0f;
	dir[Y] = 0.0f;
	dir_from_inputs(input, dir, cos(drawer->player->angle), \
	sin(drawer->player->angle));
	len = dir[X] * dir[X] + dir[Y] * dir[Y];
	if (len > 0.0f)
	{
		len = sqrtf(len);
		dir[X] /= len;
		dir[Y] /= len;
		move_player(drawer, dir[X], dir[Y]);
	}
	rotate_player_manager(input, drawer->player, drawer);
}
