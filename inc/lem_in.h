/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thansen <thansen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 23:29:55 by thansen           #+#    #+#             */
/*   Updated: 2019/08/11 16:53:47 by thansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"

typedef struct		s_fr
{
	char			*name;
	struct s_fr		*next;
	int				ign;
}					t_fr;

typedef struct		s_vertex
{
	char			*me;
	t_fr			*friends;
	struct s_vertex	*next;
	int				visited;
	int				blocked;
}					t_vertex;

typedef struct		s_data
{
	int				ant_number;
	char			*start;
	char			*end;
	t_vertex		*vertices;
}					t_data;

typedef struct		s_queue
{
	char			*name;
	int				lvl;
	int				ant_ind;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_flow
{
	t_queue			*path;
	int				length;
	int				index;
	int				ants_per_path;
	struct s_flow	*next;
}					t_flow;

char				*validity(t_data *data);

char				**separate(char *line);
int					fail_add(t_data *data, char **words, char **lines, int b);
int					start_end(t_data *data, char **words, int trigger);
int					add_vertices(t_data *data, char **words);
int					add_edges(t_data *data, char **words);
int					add_friends(t_vertex *vert, char *friend);
int					ft_arraydel(char ***array);

t_queue				*bfs(t_queue *que, t_vertex *v, char *start, char *end);
t_vertex			*look_for(t_vertex *vertices, char *vert);
t_queue				*reverse_que(t_queue *que);
int					queue(t_queue *que, char *v, int level);
t_queue				*ft_empty_queue(t_queue *que, int bool);
t_queue				*init_que(t_queue *que, char *start, int lvl);

t_queue				*find_shortest_path(t_vertex *vertices, t_queue *que);

void				delgraph(t_data *data);

int					free_everything(t_flow *flows, t_data *data, int er);
t_flow				*free_unused_flows(t_flow *flows, int needed_block);
t_flow				*flow_search(t_data *data, t_queue *path, \
								char *start, char *end);
int					solution(t_data *data, t_queue *path, char *f);

int					reset_visited(t_vertex *v, t_queue *path, \
								char *start, char *end);
int					reset_blocked(t_vertex *v);
void				set_ignore_end(t_vertex *v, char *start, char *end);
int					flow_capacity(t_vertex *v, char *start, char *end);
int					in_the_path(char *v, t_queue *path);

int					ants_distribution(t_flow *flows, int steps, int ants_left);
t_flow				*free_unused_paths(t_flow *flows);
int					count_paths_in_flow(t_flow *flow);
int					count_path_len(t_queue *path);

#endif
