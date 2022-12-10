/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GET_NEXT_LINE.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:40:16 by tgriffit          #+#    #+#             */
/*   Updated: 2022/11/22 20:31:35 by tgriffit         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	reader(int fd, char **txt, t_vars *vars)
{
	vars->bytes = (int)read(fd, vars->buffer, BUFFER_SIZE);
	vars->buffer[vars->bytes] = 0;
	if (vars->rmndr)
	{
		*txt = ft_strjoin_free(*txt, vars->rmndr, 1);
		free(vars->rmndr);
		vars->rmndr = NULL;
	}
	*txt = ft_strjoin_free(*txt, (char *)vars->buffer, 1);
}

static char	*get_line(const char *str, char **remainder)
{
	char	*line;
	size_t	linelen;
	size_t	i;

	linelen = 0;
	while (str[linelen] && str[linelen] != '\n')
		linelen++;
	line = malloc(linelen + 2);
	if (!line)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	*remainder = ft_strdup(str + i);
	line[i] = 0;
	free((void *)str);
	return (line);
}

/**
 * Returns a line read from a file descriptor
 * @param fd = File descriptor to read from
 * @return Read line: correct behavior
 * \n NULL: nothing else to read or an error occurred
*/

char	*get_next_line(int fd)
{
	char			*text;
	static t_vars	vars[1023];

	if ((fd < 0 || fd > 1023) || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, vars[fd].buffer, 0) < 0)
		return (NULL);
	text = ft_strdup("");
	if (!text)
		return (NULL);
	vars[fd].bytes = 1;
	while (!ft_strchr(text, '\n') && vars[fd].bytes > 0)
	{
		reader(fd, &text, &vars[fd]);
		if (!text)
			return (0);
	}
	if (ft_strchr(text, '\n') || (vars[fd].bytes == 0 && *text))
		return (get_line(text, &vars[fd].rmndr));
	free(text);
	return (NULL);
}
