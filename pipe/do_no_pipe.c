/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_no_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:19:32 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/21 13:13:45 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

/******************************************************************************
Redirection of the last heredoc in the pipe to stdin in parent process
******************************************************************************/
void	do_hd_fd_no_pipe(t_all *all)
{
	if (find_last_hd_int(all->pipe.pipe, all) == 1)
	{
		if (all->pipe.heredoc_fd[all->pipe.pipe][0] >= 0)
		{
			if (dup2(all->pipe.heredoc_fd[all->pipe.pipe][0], STDIN_FILENO) ==
				-1)
				error_dup2(all, all->pipe.heredoc_fd[all->pipe.pipe][0],
					"dup2");
		}
		ft_close(all, &all->pipe.heredoc_fd[all->pipe.pipe][0]);
	}
}

/******************************************************************************
Redirection of file descriptors from char *infile to stdin in parent process
******************************************************************************/
int	do_redir_in_no_pipe(t_all *all, char *redir)
{
	all->pipe.fd_infile = open(redir, O_RDONLY);
	if (all->pipe.fd_infile == -1)
		return (error_msg_no_pipe(all, redir), 1);
	if (all->pipe.fd_infile >= 0)
	{
		if (dup2(all->pipe.fd_infile, STDIN_FILENO) == -1)
			return (error_dup2(all, all->pipe.fd_infile, redir), 1);
	}
	ft_close(all, &all->pipe.fd_infile);
	return (0);
}

int	do_redir_out_no_pipe(t_all *all, char *temp, t_token_type type)
{
	if (type == REDIRECT_OUT)
		all->pipe.fd_outfile = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		all->pipe.fd_outfile = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (all->pipe.fd_outfile == -1)
		return (error_msg_no_pipe(all, temp));
	if (all->pipe.fd_outfile >= 0)
	{
		if (dup2(all->pipe.fd_outfile, STDOUT_FILENO) == -1)
			return (error_dup2(all, all->pipe.fd_outfile, temp));
	}
	ft_close(all, &all->pipe.fd_outfile);
	return (0);
}

int	do_redir_no_pipe(t_all *all)
{
	t_token	*temp;

	temp = all->rdir_tkn;
	while (temp && temp->pipe != all->pipe.pipe)
		temp = temp->next;
	do_hd_fd_no_pipe(all);
	while (temp && temp->pipe == all->pipe.pipe)
	{
		if (temp->type == REDIRECT_IN)
		{
			if (do_redir_in_no_pipe(all, temp->next->str) == 1)
				return (1);
			temp = temp->next->next;
		}
		else if (temp->type == REDIRECT_OUT || temp->type == APPEND_OUT)
		{
			if (do_redir_out_no_pipe(all, temp->next->str, temp->type) == 1)
				return (1);
			temp = temp->next->next;
		}
		else
			temp = temp->next;
	}
	return (0);
}

/******************************************************************************
No forks we are in the parent process
******************************************************************************/
int	do_no_pipe(t_all *all)
{
	all->data.stdout_original = -1;
	all->data.stdin_original = -1;
	all->data.stdout_original = dup(STDOUT_FILENO);
	if (all->data.stdout_original == -1)
		return (error_msg_no_pipe(all, "dup stdout"));
	all->data.stdin_original = dup(STDIN_FILENO);
	if (all->data.stdin_original == -1)
		return (error_msg_no_pipe(all, "dup stdin"));
	if (do_redir_no_pipe(all) == 1 || !all->pipe.cmd_args[0][0])
	{
		fd_back_origin(all, &all->data.stdout_original,
			&all->data.stdin_original);
		return (1);
	}
	all->error_code = do_built_in(all);
	fd_back_origin(all, &all->data.stdout_original, &all->data.stdin_original);
	return (all->error_code);
}
