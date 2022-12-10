/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:35:47 by tgriffit          #+#    #+#             */
/*   Updated: 2022/12/02 16:37:24 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_default_keys(t_input *input)
{
	input->key_bindings[ACTION_BACKWARD] = KEY_S;
	input->key_bindings[ACTION_FORWARD] = KEY_W;
	input->key_bindings[ACTION_STRAFE_LEFT] = KEY_A;
	input->key_bindings[ACTION_STRAFE_RIGHT] = KEY_D;
	input->key_bindings[ACTION_LEFT] = KEY_Q;
	input->key_bindings[ACTION_RIGHT] = KEY_E;
}

void	init_keyboard(t_input *input)
{
	int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		input->key_bindings[i] = -1;
		input->key_states[i] = 0;
		++i;
	}
	init_default_keys(input);
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

/**
 * Manage some keys hit. This functions is actually used for quit the app or
 * zoom in/out
 * @param keycode
 * @param drawer
 * @return Always 0.
 */
__attribute__((weak))
int	key_down_hook(int keycode, t_drawer *drawer)
{
	t_input	*input;
	int		action;

	if (keycode == KEY_ESC)
		kill_cub3d(drawer, NULL);
	input = &drawer->input;
	action = find_action_index(input, keycode);
	if (keycode == 35)
	{
		drawer->dmg_ticks = 12;
		if (drawer->health > 1)
		{
			if (drawer->health <= 10)
				drawer->health = 0;
			else
				drawer->health -= 10;
		}
	}
	if (action >= 0)
		input->key_states[action] = 1;
	return (0);
}

int	key_up_hook(int keycode, t_drawer *drawer)
{
	t_input	*input;
	int		action;

	input = &drawer->input;
	action = find_action_index(input, keycode);
	if (action >= 0)
		input->key_states[action] = 0;
	return (0);
}
