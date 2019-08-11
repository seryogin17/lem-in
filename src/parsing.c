/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:51:02 by thansen           #+#    #+#             */
/*   Updated: 2019/07/31 23:07:52 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		start_end(t_data *data, char **words, int trigger)
{
	(trigger == 's') ? (data->start = ft_strdup(words[0])) : \
		(data->end = ft_strdup(words[0]));
	return (0);
}

int		add_vertices(t_data *data, char **words)
{
	t_vertex *vert;
	t_vertex *tmp;

	vert = (t_vertex*)malloc(sizeof(t_vertex));
	vert->me = ft_strdup(words[0]);
	vert->blocked = 0;
	vert->visited = 0;
	vert->next = NULL;
	vert->friends = NULL;
	tmp = data->vertices;
	if (!data->vertices && (data->vertices = vert))
		return (0);
	while (tmp->next && ft_strcmp(tmp->me, words[0]))
		tmp = tmp->next;
	if (!tmp->next && ft_strcmp(tmp->me, words[0]))
		tmp->next = vert;
	else
	{
		free(vert->me);
		free(vert);
		return (1);
	}
	return (0);
}

int		add_friends(t_vertex *vert, char *friend)
{
	t_fr *fr;
	t_fr *tmp;

	fr = (t_fr*)malloc(sizeof(t_fr));
	fr->name = ft_strdup(friend);
	fr->next = NULL;
	fr->ign = 0;
	if (!vert->friends)
		vert->friends = fr;
	else
	{
		tmp = vert->friends;
		while (tmp->next && ft_strcmp(tmp->name, friend))
			tmp = tmp->next;
		if (!tmp->next && ft_strcmp(tmp->name, friend))
			tmp->next = fr;
		else
		{
			free(fr->name);
			free(fr);
			return (1);
		}
	}
	return (0);
}

int		add_edges(t_data *data, char **words)
{
	t_vertex	*tmp;

	tmp = data->vertices;
	while (tmp && ft_strcmp(tmp->me, words[0]) && ft_strcmp(tmp->me, words[1]))
		tmp = tmp->next;
	if (!ft_strcmp(tmp->me, words[0]) && !add_friends(tmp, words[1]))
	{
		while (tmp && ft_strcmp(tmp->me, words[1]))
			tmp = tmp->next;
		if (tmp)
			return (add_friends(tmp, words[0]));
		return (1);
	}
	else if (!ft_strcmp(tmp->me, words[1]) && !add_friends(tmp, words[0]))
	{
		while (tmp && ft_strcmp(tmp->me, words[0]))
			tmp = tmp->next;
		if (tmp)
			return (add_friends(tmp, words[1]));
		return (1);
	}
	else
		return (1);
}

int		ft_arraydel(char ***array)
{
	int	i;

	if (!array || !(*array))
		return (0);
	i = -1;
	while ((*array)[++i])
		free((*array)[i]);
	free(*array);
	*array = NULL;
	return (0);
}
