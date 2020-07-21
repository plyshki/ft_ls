/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:21:19 by pguitar           #+#    #+#             */
/*   Updated: 2019/07/22 16:21:21 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_sum(int a)
{
	int b;

	b = 0;
	while (a /= 10)
		b++;
	return (b);
}

int	ft_size_space_size(t_data **list, int j, t_data **tmp)
{
	int			i;
	static int	max_size;

	if (j == 2)
	{
		max_size = 0;
		return (1);
	}
	else if (j == 1)
	{
		max_size = ft_sum((*tmp)->size_size);
		i = ft_sum((*list)->size);
		i = max_size - i;
		ft_putchar(' ');
		ft_print_space(&i);
		return (1);
	}
	if ((*list)->size > max_size)
	{
		max_size = (*list)->size;
		(*tmp)->size_size = max_size;
	}
	return (1);
}

int	ft_size_space_grp(t_data **list, int j, t_data **tmp)
{
	int			i;
	static int	grp;

	if (j == 2)
	{
		grp = 0;
		return (1);
	}
	else if (j == 1)
	{
		i = (*tmp)->size_grp - ft_strlen((*list)->group_name);
		ft_putchar(' ');
		while (i--)
			ft_putchar(' ');
		return (1);
	}
	i = ft_strlen((*list)->group_name);
	if (i > grp)
	{
		grp = i;
		(*tmp)->size_grp = grp;
	}
	return (1);
}

int	ft_size_space_usr(t_data **list, int j, t_data **tmp)
{
	int			i;
	static int	usr;

	if (j == 2)
	{
		usr = 0;
		return (1);
	}
	else if (j == 1)
	{
		i = (*tmp)->size_usr - ft_strlen((*list)->user_name);
		ft_putchar(' ');
		while (i--)
			ft_putchar(' ');
		return (1);
	}
	i = ft_strlen((*list)->user_name);
	if (i > usr)
	{
		usr = i;
		(*tmp)->size_usr = usr;
	}
	return (1);
}

int	ft_size_space_nlink(t_data **list, int j, t_data **tmp)
{
	int			i;
	static int	max_nlink;

	if (j == 2)
	{
		max_nlink = 0;
		return (1);
	}
	else if (j == 1)
	{
		max_nlink = ft_sum((*tmp)->size_link);
		i = ft_sum((*list)->nlink);
		i = max_nlink - i;
		ft_putstr(" ");
		while (i--)
			ft_putchar(' ');
		return (1);
	}
	if ((*list)->nlink > max_nlink)
	{
		max_nlink = (*list)->nlink;
		(*tmp)->size_link = max_nlink;
	}
	return (1);
}
