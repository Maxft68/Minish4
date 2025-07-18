/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:15:12 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/18 21:15:21 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

void	initialize_data(t_all *all, char *old)
{
	all->data.z = 0;
	all->data.new = NULL;
	all->data.tmp = gc_malloc(all, ft_strlen(old) + 1);
}

void	join_to_new(t_all *all, char *val)
{
	all->data.temp = gc_strjoin(all, all->data.new, val);
	all->data.new = all->data.temp;
}
