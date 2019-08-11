/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 16:21:07 by thansen           #+#    #+#             */
/*   Updated: 2019/08/11 14:49:44 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

char	**separate(char *line)
{
	char **words;

	words = (ft_strchr(line, '-') \
		? ft_strsplit(line, '-') : ft_strsplit(line, ' '));
	return (words);
}

int		fail_add(t_data *data, char **words, char **lines, int b)
{
	if (!b)
		return (add_edges(data, words) && \
			!ft_arraydel(&words) && !ft_arraydel(&lines));
	else
		return (add_vertices(data, words) && \
				!ft_arraydel(&words) && !ft_arraydel(&lines));
}
