/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:29:36 by alavaud           #+#    #+#             */
/*   Updated: 2022/11/29 18:32:17 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <unistd.h>

static void	child_sig(int sig)
{
	(void)sig;
	(void)wait3(NULL, WNOHANG, NULL);
}

void	snd_play(const char *path)
{
	static int	handler_set = 0;
	char		*args[3];
	extern char	**environ;

	if (!handler_set)
	{
		signal(SIGCHLD, child_sig);
		handler_set = 1;
	}
	if (fork() == 0)
	{
		args[0] = "/usr/bin/afplay";
		args[1] = (char *)path;
		args[2] = NULL;
		execve(args[0], args, environ);
		_exit(1);
	}
}
