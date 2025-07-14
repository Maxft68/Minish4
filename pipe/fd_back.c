#include "../mandatory/minishell.h"

/******************************************************************************
Set stdout and stdin back to original file descriptors
******************************************************************************/
void	fd_back_origin(t_all *all, int *stdout_original, int *stdin_original)
{
	if (*stdout_original > 2)
	{
		if (dup2(*stdout_original, STDOUT_FILENO) == -1)
			error_dup2(all, *stdout_original, "STDOUT");
		ft_close(all, stdout_original);
		*stdout_original = -1;
	}
	if (*stdin_original > 2)
	{
		if (dup2(*stdin_original, STDIN_FILENO) == -1)
			error_dup2(all, *stdin_original, "STDIN");
		ft_close(all, stdin_original);
		*stdin_original = -1;
	}
}
