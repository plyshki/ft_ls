/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag_l.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:19:46 by pguitar           #+#    #+#             */
/*   Updated: 2019/07/22 16:19:51 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_readlink(t_data **list)
{
	char *buf;

	buf = (char*)malloc(sizeof(char) * NAME_MAX + 1);
	readlink((*list)->full_path, buf, NAME_MAX);
	ft_putstr((*list)->name);
	ft_putstr(" -> ");
	ft_putstr(buf);
	free(buf);
	return (1);
}

int	ft_print_flag_l_2(t_data **list, t_data **tmp)
{
	ft_putstr((*list)->t_p);
	ft_size_space_nlink(list, 1, tmp);
	ft_putnbr((*list)->nlink);
	ft_putchar(' ');
	ft_putstr((*list)->user_name);
	ft_size_space_usr(list, 1, tmp);
	ft_putchar(' ');
	ft_putstr((*list)->group_name);
	ft_size_space_grp(list, 1, tmp);
	ft_size_space_size(list, 1, tmp);
	ft_putnbr((*list)->size);
	ft_putchar(' ');
	ft_putstr((*list)->time);
	ft_putchar(' ');
	if ((*list)->t_p[0] == 'l')
		ft_readlink(list);
	else
		ft_putstr((*list)->name);
	ft_putstr("\n");
	return (1);
}

int	ft_print_flag_l_1_support(t_data **list, t_data **tmp, int i, int *j)
{
	if ((*list)->print_name == 1)
	{
		if (ft_no_printlink(list, i, j, 1))
			return (1);
		if (i == 0 || (*j)++ > 0)
			ft_putstr("\n");
		ft_putstr((*list)->name);
		ft_putstr(":\n");
		if ((*list)->next && (*list)->next->print_name != 1 &&
			ft_strstr((*list)->next->full_path, (*list)->name) != 0)
		{
			ft_putstr("total ");
			ft_putnbr((*list)->st_blocks);
			ft_putstr("\n");
		}
		(*tmp) = *list;
		(*list) = (*list)->next;
		return (1);
	}
	return (0);
}

int	ft_st_blocks(t_data **list, int *i, int *j)
{
	if ((*i)++ == 0)
	{
		(*j)++;
		ft_putstr("total ");
		ft_putnbr((*list)->st_blocks);
		ft_putstr("\n");
	}
	return (1);
}

int	ft_print_flag_l_1(t_data **list, int i)
{
	int		j;
	t_data	*tmp;

	j = 0;
	tmp = *list;
	while (*list)
	{
		if (ft_print_flag_l_1_support(list, &tmp, i, &j))
			continue;
		ft_st_blocks(list, &i, &j);
		ft_print_flag_l_2(list, &tmp);
		if ((*list)->print_file == 1)
		{
			if ((*list)->next && (*list)->next->print_file != 1)
				ft_putchar('\n');
		}
		(*list) = (*list)->next;
	}
	return (1);
}
