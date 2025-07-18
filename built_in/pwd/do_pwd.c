/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:12:50 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/18 21:38:48 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(t_all *all)
{
	char	s[4096];
	char	*f;

	if (find_the_value(all, "PWD"))
	{
		f = find_the_value(all, "PWD");
		printf("%s\n", f);
	}
	else if (getcwd(s, sizeof(s)))
		printf("%s\n", s);
	return (all->error_code = 0, 0);
}

char	*ft_pwd(t_all *all)
{
	char	s[4096];
	char	*f;

	if (find_the_value(all, "PWD"))
	{
		f = find_the_value(all, "PWD");
		return (f);
	}
	else if (getcwd(s, sizeof(s)))
	{
		f = gc_strdup_env(s, all);
		return (f);
	}
	return (NULL);
}
