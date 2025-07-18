/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:12:21 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/18 21:12:23 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mandatory/minishell.h"

int	print_and_null(t_all *all, char *s)
{
	ft_putstr_fd("write_on_me: export: `", 2);
	if (s)
		ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	all->data.n = NULL;
	all->error_code = 1;
	all->data.val = NULL;
	all->data.export_error = 1;
	return (1);
}
