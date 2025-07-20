/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:13:32 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/20 22:46:34 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

volatile sig_atomic_t	g_sigint_flag = 0;

void	reset_datas(t_all *all)
{
	all->garbage = NULL;
	all->token = NULL;
	all->rdir_tkn = NULL;
	all->pipe.heredoc_fd = NULL;
	all->pipe.pipe = 0;
	all->pipe.i = 0;
	all->pipe.nb_pipe = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_all	all;
	char	*firstinput;
	char	*input;

	if (argc != 1)
		return (printf("Too much args\n"), 1);
	ft_memset(&all, 0, sizeof(t_all));
	do_env(&all, env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signals_swing();
		firstinput = readline("write_on_me ");
		if (!firstinput)
			break ;
		// char *firstinput = readline("minishell $");
		// if (!firstinput)
		// {
		// 	if (isatty(STDIN_FILENO))
		// 	write(2, "exit\n", 6);
		// 	exit (all.error_code);
		// }
		if (g_sigint_flag)
			all.error_code = 130;
		g_sigint_flag = 0;
		input = gc_strdup_input(firstinput, &all);
		if (create_lexer(input, &all) != -1)
			pars_to_exec(&all);
		free_garbage_collect(&all.garbage);
		reset_datas(&all);
	}
	return ((void)argv, ft_exit("exit\n", &all, all.error_code), 0);
}
