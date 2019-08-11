/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:07:50 by thansen           #+#    #+#             */
/*   Updated: 2019/08/11 14:49:43 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		checknparse_vertices(char *file, t_data *data, int i)
{
	char	**lines;
	char	**words;
	char	trigger;

	lines = ft_strsplit(file, '\n');
	data->ant_number = ft_atoi(lines[0]);
	while (lines[++i] && (words = separate(lines[i])))
	{
		if (lines[i][0] == '#' && lines[i][1] != '#' && !ft_arraydel(&words))
			continue;
		if (ft_wordcount(lines[i], ' ') == 3)
		{
			trigger ? trigger = start_end(data, words, trigger) : 0;
			if (fail_add(data, words, lines, 1))
				return (1);
		}
		else if (ft_wordcount(lines[i], ' ') == 1 && ft_strchr(lines[i], '#'))
			trigger = (!ft_strcmp(lines[i], "##start\0") ? 's' : 'e');
		else if (fail_add(data, words, lines, 0))
			return (1);
		ft_arraydel(&words);
	}
	ft_arraydel(&lines);
	return (0);
}

char	*add_line(char *file, char *line, int i)
{
	char	*n;
	char	*tmp;

	n = (char*)malloc(sizeof(char) * 2);
	n[0] = '\n';
	n[1] = '\0';
	if (i == 1)
		file = ft_strdup(line);
	else
	{
		tmp = ft_strjoin(file, n);
		free(file);
		file = ft_strjoin(tmp, line);
		free(tmp);
	}
	free(n);
	return (file);
}

int		check_coordinates_and_ant_num(char *line, int first)
{
	int	i;

	i = 0;
	if (!first)
		while (line[i] != ' ')
			i++;
	while (line[i])
	{
		if (line[i] == 32 || ft_strchr("0123456789", line[i]))
			++i;
		else
			return (1);
	}
	return (0);
}

int		check_line(char *line, int i)
{
	int			wc;
	static int	prev_wc;
	static int	if_prev_edge;

	wc = ft_wordcount(line, ' ');
	if (i == 1 && check_coordinates_and_ant_num(line, 1))
		return (1);
	if (ft_strchr(line, '#'))
		return (0);
	if (wc != 1 && wc != 3)
		return (1);
	if ((i == 1 && wc != 1) || \
		(wc == 1 && prev_wc && ft_strcmp(line, "##start\0") \
			&& ft_strcmp(line, "##end\0") && !ft_strchr(line, '-') \
				&& !ft_strchr(line, '#')))
		return (1);
	if (*line == 'L' || *line == '-')
		return (1);
	if ((wc == 3 || (*line == '#' && *(line + 1) == '#')) && if_prev_edge)
		return (1);
	if (wc == 3 && check_coordinates_and_ant_num(line, 0))
		return (1);
	prev_wc = wc;
	if_prev_edge = ((wc == 1 && ft_strchr(line, '-')) ? 1 : 0);
	return (0);
}

char	*validity(t_data *data)
{
	char	*line;
	char	*file;
	int		i;

	i = 1;
	file = NULL;
	line = NULL;
	while (get_next_line(0, &line))
	{
		if (check_line(line, i))
		{
			free(line);
			if (file)
				free(file);
			return (file = NULL);
		}
		file = add_line(file, line, i++);
		free(line);
	}
	if (checknparse_vertices(file, data, i = 0))
	{
		free(file);
		return (file = NULL);
	}
	return (file);
}
