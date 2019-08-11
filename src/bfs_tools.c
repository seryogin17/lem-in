/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:42:32 by thansen           #+#    #+#             */
/*   Updated: 2019/07/29 02:01:41 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_queue		*reverse_que(t_queue *que)
{
	t_queue *next;
	t_queue *cur;
	t_queue *prev;

	cur = que;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	que = prev;
	return (que);
}

int			check_level(t_queue *que, t_vertex *v, t_queue *path, char *prev)
{
	t_vertex	*tv;
	t_fr		*tf;

	tv = look_for(v, que->name);
	tf = tv->friends;
	while (tf)
		if (!ft_strcmp(tf->name, prev) && \
			queue(path, que->name, que->lvl))
			break ;
		else
			tf = tf->next;
	if (!tf)
		return (1);
	return (0);
}

t_queue		*find_shortest_path(t_vertex *vertices, t_queue *que)
{
	t_queue		*short_path;
	t_queue		*tmp;
	int			lvl;
	char		*prev;

	que = reverse_que(que);
	short_path = NULL;
	short_path = init_que(short_path, que->name, que->lvl);
	tmp = que;
	while (que)
	{
		prev = que->name;
		lvl = que->lvl;
		while (que && que->lvl == lvl)
			que = que->next;
		while (que && que->lvl + 1 == lvl)
			if (check_level(que, vertices, short_path, prev))
				que = que->next;
			else
				break ;
	}
	ft_empty_queue(tmp, 1);
	return (short_path);
}
