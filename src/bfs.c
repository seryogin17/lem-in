/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 20:02:26 by thansen           #+#    #+#             */
/*   Updated: 2019/07/31 20:50:01 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_vertex	*look_for(t_vertex *vertices, char *vert)
{
	t_vertex	*tmp;

	tmp = vertices;
	while (tmp && ft_strcmp(tmp->me, vert))
		tmp = tmp->next;
	return (tmp);
}

int			queue(t_queue *que, char *v, int level)
{
	t_queue	*vert;
	t_queue	*tmp;

	tmp = que;
	while (tmp->next)
		tmp = tmp->next;
	vert = (t_queue*)malloc(sizeof(t_queue));
	vert->name = ft_strdup(v);
	vert->lvl = level;
	vert->ant_ind = 0;
	vert->next = NULL;
	tmp->next = vert;
	return (1);
}

t_queue		*ft_empty_queue(t_queue *que, int bool)
{
	t_queue	*t;

	while (que)
	{
		t = que->next;
		free(que->name);
		que->name = NULL;
		free(que);
		que = t;
		if (!bool)
			return (que);
	}
	que = NULL;
	return (que);
}

t_queue		*init_que(t_queue *que, char *start, int lvl)
{
	que = NULL;
	que = (t_queue*)malloc(sizeof(t_queue));
	que->name = ft_strdup(start);
	que->lvl = lvl;
	que->ant_ind = 0;
	que->next = NULL;
	return (que);
}

t_queue		*bfs(t_queue *path, t_vertex *v, char *start, char *end)
{
	t_queue		*prev;
	t_queue		*tmp;
	t_vertex	*tv;
	t_fr		*tf;

	path = init_que(path, start, 1);
	tmp = path;
	while (path && (tv = look_for(v, path->name)))
		if (!tv->visited && !tv->blocked && (tv->visited = 1))
		{
			tf = tv->friends;
			while (tf && (!tf->ign ? queue(path, tf->name, path->lvl + 1) : 1))
				tf = tf->next;
			if (!ft_strcmp(path->name, end))
				path->next = ft_empty_queue(path->next, 1);
			prev = path;
			path = path->next;
		}
		else
		{
			prev->next = path->next;
			path = ft_empty_queue(path, 0);
		}
	path = find_shortest_path(v, tmp);
	return (path);
}
