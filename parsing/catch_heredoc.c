#include "../mandatory/minishell.h"
#include <signal.h>

static char	*append_hd(char *hd_eof, t_all *all)
{
	char	*str;

	str = gc_malloc(all, sizeof(char) * 1);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	all->hd_data.hd_eof_len = ft_strlen(hd_eof);
	all->hd_data.str_len = 0;
	str = process_input_lines(str, hd_eof, all);
	return (str);
}

static void	handle_signal_interruption(t_all *all)
{
	t_token	*tmp;

	tmp = all->token;
	while (tmp)
	{
		if (tmp->type == HEREDOC && tmp->next)
			tmp->next->str = NULL;
		tmp = tmp->next;
	}
	all->error_code = 130;
}

void	catch_heredoc(t_all *all)
{
	t_token	*tmp;
	char	*str;

	tmp = all->token;
	str = NULL;
	while (tmp->next)
	{
		if (tmp->type == HEREDOC)
		{
			g_sigint_flag = 0;
			str = gc_strdup(append_hd(tmp->next->str, all), all);
			initialize_hd_data(str, all);
			if (g_sigint_flag == 1)
			{
				handle_signal_interruption(all);
				return;
			}
			if (!str)
				break ;
			if (str != NULL)
				handle_hd_expand(str, all);
			tmp->next->str = gc_strdup(all->hd_data.new, all);
		}
		tmp = tmp->next;
	}
}
