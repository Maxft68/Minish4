/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:13:32 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/20 17:06:43 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

static int    is_fd_open(int fd)
{
    int flags;
    flags = fcntl(fd, F_GETFD);
    if (flags == -1)
    {
        if (errno == EBADF)
            return (0);  // FD is not open.
        else
            perror("fcntl");
    }
    return (1); // FD appears to be open.
}

void    fd_status(char *msg, int fd)
{
    fprintf(stderr, "%s\n", msg);
    if (is_fd_open(fd))
        fprintf(stderr, "Fd %d is open\n", fd);
    else
        fprintf(stderr, "Fd %d is closed\n", fd);
}
volatile sig_atomic_t g_sigint_flag = 0;

int	main(int argc, char **argv, char **env)
{
	t_all all;

	if (argc != 1)
		return (printf("Too much args\n"), 1);
	ft_memset(&all, 0, sizeof(t_all));
	do_env(&all, env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signals_swing();
		char *firstinput = readline("write_on_me ");
		if (!firstinput)
			break;
		//char *firstinput = readline("minishell $");
		// if (!firstinput)
		// {
		// 	if (isatty(STDIN_FILENO))
		// 	write(2, "exit\n", 6);
		// 	exit (all.error_code);
		// }
		g_sigint_flag = 0;
		char *input = gc_strdup_input(firstinput, &all);
		if (create_lexer(input, &all) != -1)
			pars_to_exec(&all);
		// fd_status("rien", STDIN_FILENO);
		// fd_status("STDOUT", STDOUT_FILENO);
		free_garbage_collect(&all.garbage);
		all.garbage = NULL;
		all.token = NULL;
		all.rdir_tkn = NULL;
		all.pipe.heredoc_fd = NULL;
		all.pipe.pipe = 0;
		all.pipe.i = 0;
		all.pipe.nb_pipe = 0;
	}
	return((void)argv, ft_exit("exit\n", &all, all.error_code), 0);
}

