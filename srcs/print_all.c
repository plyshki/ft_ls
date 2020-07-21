/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:19:32 by pguitar           #+#    #+#             */
/*   Updated: 2019/07/22 16:19:35 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	*ft_strndup(const char *s1, int n)
{
	int		i;
	int		tmp;
	char	*s2;

	i = 0;
	tmp = n;
	while (s1[i] != '\0' && i < n)
		i++;
	if (!(s2 = (char *)malloc((sizeof(*s1)) * (i + 1))))
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < tmp)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int		ft_print_name_dir(char *name, t_direct **d_list, t_data **list)
{
	static int i;

	if ((*d_list) && (*d_list)->sum > 0 && i == 0)
	{
		i = 1;
		ft_add_argv_list(ft_strdup(name), list);
	}
	else if ((*d_list) && (*d_list)->sum > 0)
	{
		ft_add_argv_list(ft_strdup(name), list);
	}
	else if (!(ft_strlen(name) == 1 && name[0] == '.') ||
			((i == 1) && !(ft_strlen(name) == 1 && name[0] == '.')))
	{
		ft_add_argv_list(ft_strdup(name), list);
	}
	return (1);
}

int		ft_print_all_2(t_data **list, int i, int *j)
{
	while (*list)
	{
		if ((*list)->print_name == 1)
		{
			if (ft_no_printlink(list, i, j, 0))
				continue;
			if (i == 0 || (*j)++ > 0)
				ft_putstr("\n");
			ft_putstr((*list)->name);
			ft_putstr(":\n");
			(*list) = (*list)->next;
			continue;
		}
		ft_putstr((*list)->name);
		ft_putstr("\n");
		if ((*list)->print_file == 1 && (*list)->next->print_file == 0)
			ft_putstr("\n");
		(*list) = (*list)->next;
	}
	return (1);
}

int		ft_print_all_1(t_data **list, t_flag *flags, int i)
{
	int		j;
	t_data	*l_list;

	j = 0;
	l_list = (*list);
	if ((*list) && flags->l == 1)
		ft_flag_l(&l_list, i);
	else
		ft_print_all_2(&l_list, i, &j);
	return (1);
}

int		ft_fill(int *j, int *k)
{
	(*j) = 1;
	(*k) = 2;
	return (1);
}
