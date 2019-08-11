/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_search_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:58:49 by thansen           #+#    #+#             */
/*   Updated: 2019/07/31 17:28:43 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		reset_visited(t_vertex *v, t_queue *path, char *start, char *end)
{
	t_vertex	*t;

	t = v;
	while (v)
	{
		if (!v->blocked && in_the_path(v->me, path) && \
				ft_strcmp(v->me, start) && ft_strcmp(v->me, end))
			v->blocked = 1;
		v = v->next;
	}
	while (t)
	{
		if (t->visited)
			t->visited = 0;
		t = t->next;
	}
	return (0);
}

int		reset_blocked(t_vertex *v)
{
	while (v)
	{
		v->visited = 0;
		v->blocked = 0;
		v = v->next;
	}
	return (1);
}

void	set_ignore_end(t_vertex *v, char *start, char *end)
{
	t_fr	*fr;

	while (v)
		if (!ft_strcmp(v->me, start))
			break ;
		else
			v = v->next;
	fr = v->friends;
	while (fr)
		if (!ft_strcmp(fr->name, end) && (fr->ign = 1))
			return ;
		else
			fr = fr->next;
}

int		flow_capacity(t_vertex *v, char *start, char *end)
{
	t_vertex	*tv;
	t_fr		*tf;
	int			i;
	int			j;

	j = 0;
	i = 0;
	tv = look_for(v, start);
	tf = tv->friends;
	while (tf && ++i)
		tf = tf->next;
	tv = look_for(v, end);
	tf = tv->friends;
	while (tf && ++j)
		tf = tf->next;
	return (i > j ? j : i);
}

int		in_the_path(char *v, t_queue *path)
{
	while (path)
	{
		if (ft_strcmp(path->name, v))
			path = path->next;
		else
			return (1);
	}
	return (0);
}
