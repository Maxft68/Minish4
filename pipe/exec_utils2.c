/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbier <rbier@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:49:55 by rbier             #+#    #+#             */
/*   Updated: 2025/07/21 16:51:55 by rbier            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

static void	get_code_error(t_all *all, int n)
{
	all->error_code = n + 128;
}

static void	update_minishell_code(t_all *all, int n)
{
	if (n >= 0 && n < 256)
		all->error_code = n;
	else if (n >= 256)
		all->error_code = n % 256;
	else
		all->error_code = (n % 256) + 256;
}

void	waiting_zzz(t_all *all, int i, int *status)
{
	while (i < all->pipe.nb_pipe + 1)
	{
		waitpid(all->pipe.pid[i], status, 0);
		if (WIFEXITED(*status))
			update_minishell_code(all, WEXITSTATUS(*status));
		else if (WIFSIGNALED(*status))
		{
			if (WTERMSIG(*status) == 2)
				printf("\n");
			else if (WTERMSIG(*status) == 3)
				printf("Quit\n");
			get_code_error(all, WTERMSIG(*status));
		}
		i++;
	}
}
