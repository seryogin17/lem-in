/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:01:45 by thansen           #+#    #+#             */
/*   Updated: 2019/08/11 20:13:47 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		count_complexity(t_flow *flows, int num_ants, int min_comp_ind)
{
	int		cur_ind;
	int		comp;
	int		min_comp;
	int		path_num;
	int		total_len;

	cur_ind = 1;
	while (flows)
	{
		total_len = 0;
		path_num = 0;
		while (flows && flows->index == cur_ind && \
					(total_len += flows->length) && ++path_num)
			flows = flows->next;
		comp = ((total_len + num_ants) / path_num) - 1;
		cur_ind == 1 ? min_comp = comp : 0;
		if (min_comp > comp && (min_comp = comp))
			min_comp_ind = cur_ind;
		++cur_ind;
	}
	return (min_comp_ind);
}

int		make_a_step(t_flow *flows, int num)
{
	t_queue		*path;
	int			cur;
	int			temp;
	static int	i = 0;
	int			prev;

	prev = i;
	path = flows->path;
	if (num)
		path->ant_ind = num;
	temp = 0;
	while (path)
	{
		cur = path->ant_ind;
		path->ant_ind = temp;
		path->ant_ind ? (ft_printf("L%d-%s ", path->ant_ind, path->name) \
						&& ++i) : 0;
		temp = cur;
		path = path->next;
	}
	if (prev == i)
		return (-1);
	return (num ? ++num : 0);
}

void	march(t_flow *flows, int num_ants)
{
	t_flow			*tmp;
	static int		key = 0;
	static int		num = 1;
	int				len;

	tmp = flows;
	len = count_paths_in_flow(flows);
	while (!key)
	{
		flows = tmp;
		while (flows && num <= num_ants)
		{
			num = make_a_step(flows, num);
			if (num > num_ants)
				num = 0;
			if (num == -1 && !(num = 0))
				--len;
			else
				len = count_paths_in_flow(tmp);
			if (!len && (key = 1))
				break ;
			flows = flows->next;
		}
		!key ? ft_printf("\n") : 0;
	}
}

t_flow	*launch_the_march(t_flow *flows, int num_ants)
{
	t_flow	*tmp;
	int		n;
	int		total_len;
	int		steps;
	int		ants_left;

	n = 0;
	tmp = flows;
	total_len = 0;
	while (flows && ++n && (total_len += flows->length))
		flows = flows->next;
	steps = (total_len + num_ants) / n;
	flows = tmp;
	ants_left = ants_distribution(flows, steps, num_ants);
	while (flows && ants_left-- && ++(flows->ants_per_path))
		flows = flows->next;
	flows = free_unused_paths(tmp);
	tmp = flows;
	while (flows)
	{
		flows->path = reverse_que(flows->path);
		flows = flows->next;
	}
	tmp ? march(tmp, num_ants) : 0;
	return (tmp);
}

int		solution(t_data *data, t_queue *path, char *f)
{
	t_flow	*flows;
	int		min_comp_ind;

	min_comp_ind = 1;
	flows = flow_search(data, path, data->start, data->end);
	flows ? min_comp_ind = count_complexity(flows, data->ant_number, min_comp_ind) : 0;
	flows ? flows = free_unused_flows(flows, min_comp_ind) : 0;
	if (flows)
	{
		ft_printf("%s\n\n", f);
		flows = launch_the_march(flows, data->ant_number);
		free(f);
	}
	else
	{
		ft_printf("ERROR\n");
		free(f);
	}
	return (flows ? free_everything(flows, data, 0) : 0);
}
