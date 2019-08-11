/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:12:51 by thansen           #+#    #+#             */
/*   Updated: 2019/08/11 17:11:59 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	delgraph(t_data *data)
{
	t_vertex	*v;
	t_vertex	*tv;
	t_fr		*f;
	t_fr		*tf;

	v = data->vertices;
	free(data->start);
	free(data->end);
	while (v)
	{
		free(v->me);
		f = v->friends;
		while (f)
		{
			free(f->name);
			tf = f->next;
			free(f);
			f = tf;
		}
		tv = v->next;
		free(v);
		v = tv;
	}
	free(data);
}

t_flow	*free_unused_flows(t_flow *flows, int needed_block)
{
	t_flow	*tmp;
	t_flow	*res;

	while (flows && flows->index != needed_block)
	{
		tmp = flows->next;
		ft_empty_queue(flows->path, 1);
		free(flows);
		flows = tmp;
	}
	res = flows;
	while (flows->next && flows->next->index == needed_block)
		flows = flows->next;
	tmp = flows->next;
	flows->next = NULL;
	flows = tmp;
	while (flows)
	{
		tmp = flows->next;
		ft_empty_queue(flows->path, 1);
		free(flows);
		flows = tmp;
	}
	return (res);
}

int		free_everything(t_flow *flows, t_data *data, int er)
{
	t_flow	*tmp;

	while (flows)
	{
		tmp = flows->next;
		flows->path = ft_empty_queue(flows->path, 1);
		free(flows);
		flows = tmp;
	}
	if (data)
		delgraph(data);
	return (er);
}
