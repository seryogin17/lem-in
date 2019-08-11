/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 17:23:15 by thansen           #+#    #+#             */
/*   Updated: 2019/08/11 17:01:13 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		ants_distribution(t_flow *flows, int steps, int ants_left)
{
	int	tmp;

	while (flows)
	{
		tmp = steps - flows->length;
		flows->ants_per_path = (tmp > 0 && tmp <= ants_left ? tmp : 0);
		ants_left -= flows->ants_per_path;
		if (ants_left <= 0)
			break ;
		flows = flows->next;
	}
	return (ants_left);
}

t_flow	*free_unused_paths(t_flow *flows)
{
	t_flow	*tmp;
	t_flow	*prev;
	t_flow	*res;

	while (flows && !flows->ants_per_path)
	{
		tmp = flows->next;
		ft_empty_queue(flows->path, 1);
		free(flows);
		flows = tmp;
	}
	prev = flows;
	res = flows;
	while ((flows = prev->next))
	{
		if (!flows->ants_per_path)
		{
			ft_empty_queue(flows->path, 1);
			prev->next = flows->next;
			free(flows);
		}
		else
			prev = flows;
	}
	return (res);
}

int		count_paths_in_flow(t_flow *flow)
{
	int	i;

	i = 0;
	while (flow && ++i)
		flow = flow->next;
	return (i);
}

int		count_path_len(t_queue *path)
{
	int	i;

	i = 0;
	while (path)
	{
		++i;
		path = path->next;
	}
	return (i);
}
