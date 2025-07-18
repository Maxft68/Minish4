/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:11:58 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/18 21:37:07 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

int	ft_str_digit(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
}

/*******************************************************************************
Only if i'm not a child write exit before exit.
*******************************************************************************/
void	im_a_child(t_all *all)
{
	if (all->pipe.nb_pipe != 0)
		return ;
	ft_putstr_fd("exit\n", 2);
}

void	puts_fdback_exit(t_all *all)
{
	ft_putstr_fd("write_on_me: exit: ", 2);
	ft_putstr_fd(all->pipe.cmd_args[all->pipe.pipe][1], 2);
	fd_back_origin(all, &all->data.stdout_original,
		&all->data.stdin_original);
	ft_exit(": numeric argument required\n", all, 2);
}
