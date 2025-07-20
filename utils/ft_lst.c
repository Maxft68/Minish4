/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:22:22 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/20 16:57:53 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	if (type == COMMAND)
		return ("COMMAND");
	if (type == ARG)
		return ("ARG");
	if (type == SQ_STRING)
		return ("SQ_STRING");
	if (type == DQ_STRING)
		return ("DQ_STRING");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == APPEND_OUT)
		return ("APPEND_OUT");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == REDIR_FILE)
		return ("REDIR_FILE");
	if (type == HD_EOF)
		return ("HD_EOF");
	if (type == ILLEGAL)
		return ("ILLEGAL");
	return ("UNKNOWN");
}

void	ft_lstadd_front(t_garbage **garbage, t_garbage *new)
{
	t_garbage	*second;

	if (!(*garbage))
	{
		*garbage = new;
		return ;
	}
	second = *garbage;
	new->next = second;
	*garbage = new;
	return ;
}

void	ft_lstadd_back_env(t_all *all, t_env **env, t_env *new)
{
	t_env	*current;

	if (!*env)
	{
		*env = new;
		all->env_export.nb_line_env++;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
	all->env_export.nb_line_env++;
	return ;
}

t_env	*ft_lstnew_env(t_all *all, char *name, char *value)
{
	t_env	*new;

	new = gc_malloc_env(all, sizeof(t_env));
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_lstclear(t_token **token)
{
	t_token	*temp;

	while (*token && token)
	{
		temp = (*token)->next;
		(*token)->str = NULL;
		*token = temp;
	}
}
