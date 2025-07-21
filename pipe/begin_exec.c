/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:19:21 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/21 16:49:27 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

static int	pipe_or_not_pipe(t_all *all)
{
	if (all->pipe.nb_pipe < 1 && (is_built_in(all) == 0
			|| !all->pipe.cmd_args[0][0]))
	{
		if (do_no_pipe(all) == 1)
			return (1);
		return (0);
	}
	else
		do_pipe(all);
	return (0);
}

int	nb_cmd(t_all *all)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = all->token;
	while (tmp)
	{
		if (tmp->type == 3)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	alloc_all(t_all *all)
{
	alloc_my_pipe_fd(all);
	alloc_my_herdoc_fd(all);
}

int	exec_part(t_all *all)
{
	int	status;
	int	i;
	int	forked;

	i = 0;
	status = 0;
	forked = 1;
	all->pipe.pid = gc_malloc(all, sizeof(pid_t) * (all->pipe.nb_pipe + 1));
	memset(all->pipe.pid, 0, sizeof(pid_t) * (all->pipe.nb_pipe + 1));
	alloc_all(all);
	while (i < all->pipe.nb_pipe + 1)
	{
		pipe_or_not_pipe(all);
		if (((all->pipe.nb_pipe == 0 && is_built_in(all) == 0)
				|| nb_cmd(all) == 0))
			forked = 0;
		close_fd_and_hd_fd(all, i);
		i++;
		all->pipe.pipe++;
	}
	i = 0;
	all->pipe.pipe = 0;
	if (forked == 1)
		waiting_zzz(all, i, &status);
	return (all->pipe.i = 0, all->pipe.pipe = 0, all->pipe.nb_pipe = 0, 0);
}
