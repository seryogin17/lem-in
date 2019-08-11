/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 19:50:57 by thansen           #+#    #+#             */
/*   Updated: 2019/08/11 17:12:41 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		main(void)
{
	t_data		*data;
	t_queue		*path;
	char		*file;

	data = (t_data *)malloc(sizeof(t_data));
	data->vertices = NULL;
	data->end = NULL;
	data->start = NULL;
	path = NULL;
	file = validity(data);
	if (file && data->start && data->end)
		solution(data, path, file);
	else
	{
		ft_printf("ERROR\n");
		if (file)
			free(file);
		if (data)
			delgraph(data);
		return (0);
	}
	return (0);
}
