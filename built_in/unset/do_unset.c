/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:12:58 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/18 21:38:32 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	suppr_env(t_all *all, char *name)
{
	t_env	*current;

	if (!all->env)
		return ;
	current = all->env;
	if (ft_strcmp(current->name, name) == 0)
	{
		current = current->next;
		all->env = current;
		all->env_export.nb_line_env--;
		return ;
	}
	while (current->next)
	{
		if (ft_strcmp(current->next->name, name) == 0)
		{
			if (!current->next->next)
			{
				current->next = NULL;
				return ;
			}
			current->next = current->next->next;
		}
		current = current->next;
	}
}

void	unset_arg(t_all *all, char *s)
{
	if (search_env(all, s) == 0)
	{
		suppr_env(all, s);
		all->env_export.nb_line_env--;
	}
}

int	do_unset(t_all *all)
{
	int		x;
	char	*s;

	x = 0;
	while (all->pipe.cmd_args[all->pipe.nb_pipe][1 + x])
	{
		all->data.val = NULL;
		all->data.n = NULL;
		s = gc_strdup_env(all->pipe.cmd_args[all->pipe.nb_pipe][1 + x], all);
		unset_arg(all, s);
		x++;
	}
	return (0);
}
