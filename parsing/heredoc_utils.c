/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:15:43 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/21 16:36:19 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"
#include <stdbool.h>

int	find_last_hd_int(int pipe, t_all *all)
{
	t_token	*tmp;
	int		redir;

	tmp = all->rdir_tkn;
	redir = 0;
	while (tmp && tmp->pipe != pipe)
		tmp = tmp->next;
	if (tmp && tmp->pipe == pipe)
	{
		while (tmp->next && tmp->next->pipe == pipe)
		{
			if (tmp->type == HEREDOC && tmp->next)
				redir = 1;
			if (tmp->type == REDIRECT_IN)
				redir = 0;
			tmp = tmp->next;
		}
	}
	return (redir);
}

void	initialize_hd_data(char *old, t_all *all)
{
	all->hd_data.i = 0;
	all->hd_data.new = NULL;
	all->hd_data.tmp2 = gc_malloc(all, ft_strlen(old) + 1);
}

void	hd_join_to_new(t_all *all, char *val)
{
	all->hd_data.tmp = gc_strjoin(all, all->hd_data.new, val);
	all->hd_data.new = all->hd_data.tmp;
}

bool	as_quotes(char *str)
{
	bool	quote;

	quote = false;
	while (str && *str)
	{
		if (*str == 34 || *str == 39)
			quote = true;
		str++;
	}
	return (quote);
}

char	*find_last_hd(int pipe, t_all *all)
{
	t_token	*tmp;
	char	*redir;

	tmp = all->rdir_tkn;
	redir = NULL;
	while (tmp && tmp->pipe != pipe)
		tmp = tmp->next;
	if (tmp && tmp->pipe == pipe)
	{
		while (tmp->next && tmp->next->pipe == pipe)
		{
			if (tmp->type == HEREDOC && tmp->next)
				redir = tmp->next->str;
			if (tmp->type == REDIRECT_IN)
				redir = NULL;
			tmp = tmp->next;
		}
	}
	return (redir);
}
