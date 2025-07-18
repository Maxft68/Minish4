/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:23:13 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/07/18 21:23:18 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strjoin(t_all *all, char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s1s2;

	if (!s1 || !s2)
		return (NULL);
	s1s2 = (char *)gc_malloc(all, (ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof(char));
	i = 0;
	j = 0;
	while (s1[i])
	{
		s1s2[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s1s2[i++] = s2[j];
		j++;
	}
	s1s2[i] = '\0';
	return (s1s2);
}

char	*gc_strjoin3(char *s1, char *s2, char *s3, t_all *all)
{
	char	*s4;
	char	*s5;

	s4 = gc_strjoin(all, s1, s2);
	s5 = gc_strjoin(all, s4, s3);
	return (s5);
}

char	*gc_strjoin_env(t_all *all, char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s1s2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	s1s2 = (char *)gc_malloc_env(all, (ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof(char));
	i = 0;
	j = 0;
	while (s1[i])
	{
		s1s2[i] = s1[i];
		i++;
	}
	while (s2[j])
		s1s2[i++] = s2[j++];
	s1s2[i] = '\0';
	return (s1s2);
}
