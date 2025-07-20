
#include "../mandatory/minishell.h"

static void sigint_hd(int signum)
{
	if (signum == SIGINT)
	{
		g_sigint_flag = 1;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		// rl_redisplay();
		close(STDIN_FILENO);
		return ;
	}
}

static void hd_abort_error(char *eof)
{
	ft_putstr_fd("minishell: warning: here-document", STDOUT_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDOUT_FILENO);
	ft_putstr_fd(eof, STDOUT_FILENO);
	ft_putstr_fd("')\n", STDOUT_FILENO);

}

static char	*append_line(char *str, char *line, t_all *all)
{
	size_t	line_len;
	size_t	new_len;
	char	*new_str;

	if (line == NULL)
		return (str);
	line_len = ft_strlen(line);
	new_len = all->hd_data.str_len + line_len + 2;
	new_str = gc_malloc(all, new_len);
	if (new_str == NULL)
		return (NULL);
	if (all->hd_data.str_len > 0 && str != NULL)
		ft_memcpy(new_str, str, all->hd_data.str_len);
	ft_memcpy(new_str + all->hd_data.str_len, line, line_len);
	new_str[all->hd_data.str_len + line_len] = '\n';
	new_str[all->hd_data.str_len + line_len + 1] = '\0';
	all->hd_data.str_len = all->hd_data.str_len + line_len + 1;
	return (new_str);
}

static char	*process_line(char *line, char *str, char *hd_eof, t_all *all)
{
	char	*new_str = NULL;

	if (line == NULL)
	{
		if (g_sigint_flag == 0)
		{
			hd_abort_error(hd_eof);
			g_sigint_flag = 2;
		}
		return (NULL);
	}
	if (g_sigint_flag == 1)
	{
		str = NULL;
		return (NULL);
	}
	if (ft_strncmp(line, hd_eof, all->hd_data.hd_eof_len) == 0
		&& ft_strlen(line) == all->hd_data.hd_eof_len)
	{
		free(line);
		return (NULL);
	}
	new_str = append_line(str, line, all);
	free(line);
	return (new_str);
}

char	*process_input_lines(char *str, char *hd_eof, t_all *all)
{
	char	*line;
	char	*new_str;
	int		save_stdin;

	save_stdin = dup(STDIN_FILENO);
	signal(SIGINT, &sigint_hd);
	while (1)
	{
		line = readline("> ");
		new_str = process_line(line, str, hd_eof, all);
		if (new_str == NULL)
			break ;
		str = new_str;
	}
	dup2(save_stdin, STDIN_FILENO);
	return (close(save_stdin), str);
}
