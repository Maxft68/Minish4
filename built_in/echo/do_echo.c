/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:02:40 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/18 21:11:08 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mandatory/minishell.h"

void	write_all(t_all *all, int pipe)
{
	char	***args;

	args = all->pipe.cmd_args;
	all->built_in.i = 0;
	while (args[pipe][all->built_in.j][all->built_in.i])
		ft_putchar(args[pipe][all->built_in.j][all->built_in.i++]);
	all->built_in.j++;
	if (all->built_in.j > 1 && args[pipe][all->built_in.j] != NULL
		&& args[pipe][all->built_in.j - 1])
		ft_putchar(' ');
}

int	do_echo(t_all *all, char ***args, int pipe)
{
	all->built_in.n = 0;
	all->built_in.j = 1;
	if (!args[pipe] || !args[pipe][all->built_in.j])
		return (ft_putchar('\n'), 0);
	while (args[pipe][all->built_in.j] && args[pipe][all->built_in.j][0] == '-'
		&& args[pipe][all->built_in.j][1] == 'n')
	{
		all->built_in.n = 1;
		all->built_in.i = 2;
		while (args[pipe][all->built_in.j][all->built_in.i] == 'n')
			all->built_in.i++;
		if (args[pipe][all->built_in.j][all->built_in.i] == '\0')
			all->built_in.j++;
		else
		{
			all->built_in.n = 0;
			break ;
		}
	}
	while (args[pipe][all->built_in.j])
		write_all(all, pipe);
	if (all->built_in.n == 0)
		ft_putchar('\n');
	return (0);
}
