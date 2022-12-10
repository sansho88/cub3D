/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:07:10 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/02 15:19:52 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mouse_up(int button, int x, int y, t_drawer *drawer)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		mlx_mouse_show();
		drawer->is_grabbing = 0;
	}
	return (0);
}

int	mouse_moved(int x, int y, t_drawer *drawer)
{
	int	delta_x;
	int	delta_y;

	if (drawer->is_grabbing)
	{
		delta_x = x - drawer->grab_x;
		delta_y = y - drawer->grab_y;
		drawer->player->angle -= delta_x * 0.01f;
		drawer->look_pitch -= delta_y * 16.0f;
		if (drawer->look_pitch < -MAX_LOOK_PITCH)
			drawer->look_pitch = -MAX_LOOK_PITCH;
		else if (drawer->look_pitch > MAX_LOOK_PITCH)
			drawer->look_pitch = MAX_LOOK_PITCH;
		player_clamp_angle(drawer);
		mlx_mouse_move(drawer->window, drawer->grab_x, drawer->grab_y);
	}
	return (0);
}

int	mouse_down(int button, int x, int y, t_drawer *drawer)
{
	if (button == 1)
	{
		mlx_mouse_hide();
		drawer->is_grabbing = 1;
		drawer->grab_x = x;
		drawer->grab_y = y;
	}
	return (0);
}

int	loop_hook(void *param)
{
	t_drawer	*drawer;

	drawer = param;
	process_inputs(drawer);
	render_frame(drawer);
	return (0);
}
