/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:24:12 by thansen           #+#    #+#             */
/*   Updated: 2019/08/11 20:08:14 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int			check(t_queue *que, char *start, char *end)
{
	if (!ft_strcmp(que->name, end))
	{
		if (!ft_strcmp(que->next->name, start))
			return (1);
		else
			return (0);
	}
	return (2);
}

t_queue		*path_merge(t_queue *first_part, t_queue *second_part)
{
	t_queue *tmp;

	tmp = second_part;
	while (second_part->next)
		second_part = second_part->next;
	first_part = ft_empty_queue(first_part, 0);
	second_part->next = first_part;
	return (tmp);
}

t_flow		*add_to_flow(t_flow *flow, t_queue *path, int bool)
{
	t_flow		*new;
	t_flow		*tmp;
	static int	index = 1;

	new = (t_flow*)malloc(sizeof(t_flow));
	new->next = NULL;
	new->path = path;
	new->ants_per_path = 0;
	new->index = 0;
	new->length = count_path_len(path);
	if (!flow && (flow = new))
	{
		flow->index = index;
		return (flow);
	}
	else
	{
		tmp = flow;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (bool)
		++index;
	return ((1 && (tmp->next->index = index)) ? flow : 0);
}

int			dupl(t_flow *flows, t_queue *path)
{
	t_queue	*tmp;
	t_queue *path_tmp;

	while (flows)
	{
		path_tmp = path;
		tmp = flows->path;
		while (tmp && path_tmp)
		{
			if (ft_strcmp(tmp->name, path_tmp->name))
				break ;
			tmp = tmp->next;
			path_tmp = path_tmp->next;
		}
		if (!tmp && !path_tmp)
			return (1);
		flows = flows->next;
	}
	return (0);
}

t_flow		*flow_search(t_data *data, t_queue *path, char *start, char *end)
{
	int		ch;
	int		max_fl;
	int		path_n;
	t_flow	*flows;

	flows = NULL;
	path_n = 0;
	max_fl = flow_capacity(data->vertices, start, end);
	while ((path_n < max_fl) && (path = bfs(path, data->vertices, start, end)))
	{
		if ((ch = check(path, start, end)) && ch == 1)
			set_ignore_end(data->vertices, start, end);
		++path_n;
		if (path_n == max_fl && dupl(flows, path) && !ft_empty_queue(path, 1))
			break ;
		if (!ft_strcmp(path->name, start))
		{
			ft_empty_queue(path, 1);
			free_everything(flows, data, 1);
			return (NULL);
		}
		if (ch == 2 && reset_blocked(data->vertices))
		{
			path = path_merge(path, bfs(path, data->vertices, path->name, end));
			if (path_n <= max_fl)
				max_fl += 1;
		}
		reset_visited(data->vertices, path, start, end);
		flows = add_to_flow(flows, path, ch == 2 ? 1 : 0);
	}
	return (flows);
}
