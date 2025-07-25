/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:12:13 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/18 21:40:53 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mandatory/minishell.h"

/*******************************************************************************
If the name exist AND with += => join
*******************************************************************************/
void	add_env(t_all *all, char *name, char *value)
{
	t_env	*current;

	if (!all->env || !name)
		return ;
	current = all->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (value)
				current->value = gc_strjoin_env(all, current->value, value);
			else
				current->value = gc_strdup_env("", all);
			return ;
		}
		current = current->next;
	}
}

void	add_value_envtwo(t_all *all)
{
	if (all->data.n)
	{
		if (all->data.egal == 1 && search_env(all, all->data.n) == 0)
			add_env(all, all->data.n, all->data.val);
		else if (search_env(all, all->data.n) == 1)
			ft_lstadd_back_env(all, &all->env, ft_lstnew_env(all, all->data.n,
					all->data.val));
	}
}

/******************************************************************************
If we have '+='
******************************************************************************/
void	add_value_env(t_all *all, char *s)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=' && i > 0 && s[i - 1] == '+')
	{
		all->data.egal = 1;
		tmp = gc_substr_env(s, 0, i - 1, all);
		if (is_alpha_str(tmp) == 0)
			print_and_null(all, s);
		else
			all->data.n = gc_strdup_env(tmp, all);
		if (s[i + 1] && all->data.n)
			all->data.val = gc_strdup_env(gc_substr_env(s, i + 1, ft_strlen(s)
						- i - 1, all), all);
		else if (all->data.n)
			all->data.val = gc_strdup_env("", all);
	}
	add_value_envtwo(all);
}

/******************************************************************************
If we have just '='
******************************************************************************/
void	do_add_env_next(t_all *all, char *s)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (i == 0)
		print_and_null(all, s);
	else if (s[i] == '=' && i > 0)
	{
		all->data.egal = 1;
		tmp = gc_substr_env(s, 0, i, all);
		if (is_alpha_str(tmp) == 0)
			print_and_null(all, s);
		else
			all->data.n = gc_strdup_env(tmp, all);
		if (s[i + 1] && all->data.n)
			all->data.val = gc_strdup_env(gc_substr_env(s, i + 1, ft_strlen(s)
						- i - 1, all), all);
		else if (all->data.n)
			all->data.val = gc_strdup_env("", all);
	}
}

/******************************************************************************
Check if just print or add a new node env
******************************************************************************/
int	do_export(t_all *all)
{
	if (ft_strncmp(all->pipe.cmd_args[all->pipe.pipe][0], "export", 6) == 0
		&& all->pipe.cmd_args[all->pipe.pipe][0][6] == '\0'
		&& all->pipe.cmd_args[all->pipe.pipe][1] == NULL)
	{
		all->export = NULL;
		copy_list(all);
		sort_list(all);
		print_export(all->export);
		return (0);
	}
	else if (ft_strncmp(all->pipe.cmd_args[all->pipe.pipe][0], "export", 6) == 0
		&& all->pipe.cmd_args[all->pipe.pipe][0][6] == '\0'
		&& (all->pipe.cmd_args[all->pipe.pipe][1] != NULL))
		return (do_add_env(all));
	return (0);
}
