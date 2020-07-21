/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:18:22 by pguitar           #+#    #+#             */
/*   Updated: 2019/08/06 14:18:27 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_ft_ft_2(t_data **list, t_flag *flags)
{
	char		*tmp;
	static int	i;

	if (i > 0 && flags->rr)
	{
		if ((*list)->print_name == 1)
			return (1);
		tmp = (*list)->full_path;
		*list = (*list)->next;
		while (*list)
		{
			if ((*list)->print_name == 1 && ft_strstr1((*list)->name, tmp) != 0)
				break ;
			else
				*list = (*list)->next;
		}
	}
	i = 1;
	return (1);
}

int	ft_ft_ft(t_data **list, t_flag *flags)
{
	if (flags->rr && (*list) && (*list)->print_name == 1)
		*list = (*list)->next;
	return (1);
}

int	ft_simple_flags_1(t_flag *flags, char *name, DIR **dir, t_data **tmp_list)
{
	int				j;
	char			*tmp;
	struct dirent	*ptr;

	j = 0;
	while ((ptr = readdir(*dir)) != NULL)
	{
		if (ptr->d_name[0] == '.' && flags->a == 0)
			continue;
		tmp = ft_strjoin(name, "/");
		ft_add_list(ft_strdup(ptr->d_name), tmp_list,
				ft_strjoin(tmp, ptr->d_name));
		j++;
		free(tmp);
	}
	closedir(*dir);
	*dir = NULL;
	return (j);
}

int	ft_simple_flags_2(t_data **list, t_data **member,
		t_flag *flags, t_direct **d_list)
{
	static int i;

	ft_ft_ft_2(list, flags);
	*list = ft_sort_list(list);
	if ((*flags).t == 1)
		*list = ft_sort_list_time(list);
	if ((*flags).r == 1)
		ft_sort_list_reverse_1(list);
	if (i++ == 0 || d_list)
		*member = *list;
	ft_ft_ft(list, flags);
	return (1);
}

int	ft_simple_flags_3(DIR **dir, t_data **list, int *j, int i)
{
	if (i == 1 && (*j)-- == 0)
	{
		if (*dir)
			closedir(*dir);
		return (1);
	}
	else if (i == 2 && (((*list)->name[0] == '.' && (*list)->name[1] == '\0')
			|| ((*list)->name[0] == '.' && (*list)->name[1] == '.'
					&& (*list)->name[2] == '\0')))
		return (1);
	return (0);
}
