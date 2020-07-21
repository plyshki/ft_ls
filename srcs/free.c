/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:16:39 by pguitar           #+#    #+#             */
/*   Updated: 2019/07/22 16:16:58 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_free_fdir(t_direct **dir, t_file **file)
{
	t_file		*tmp_f;
	t_direct	*tmp_dir;

	while ((*dir))
	{
		if ((*dir)->str)
			free((*dir)->str);
		tmp_dir = (*dir)->next;
		free(*dir);
		(*dir) = tmp_dir;
	}
	while ((*file))
	{
		tmp_f = (*file)->next;
		free(*file);
		(*file) = tmp_f;
	}
	return (1);
}

int		ft_free_lflag_clist(t_data **list)
{
	t_data *tmp_list;

	while ((*list))
	{
		tmp_list = (*list)->next;
		if ((*list)->print_name == 0 && (*list)->user_name)
			free((*list)->user_name);
		if ((*list)->print_name == 0 && (*list)->group_name)
			free((*list)->group_name);
		if ((*list)->print_name == 0 && (*list)->time)
			free((*list)->time);
		if ((*list)->name)
			free((*list)->name);
		if ((*list)->print_name == 0 && (*list)->full_path)
			free((*list)->full_path);
		free(*list);
		(*list) = tmp_list;
	}
	return (1);
}

int		ft_free_clist(t_data **list)
{
	t_data *tmp_list;

	while ((*list))
	{
		tmp_list = (*list)->next;
		if ((*list)->print_name == 1)
		{
			if ((*list)->name)
				free((*list)->name);
			free(*list);
			(*list) = tmp_list;
			continue;
		}
		if ((*list)->name)
			free((*list)->name);
		if ((*list)->full_path)
			free((*list)->full_path);
		free(*list);
		(*list) = tmp_list;
	}
	return (1);
}

t_data	*ft_swap_list(t_data *ptr1, t_data *ptr2)
{
	ptr1->next = ptr2->next;
	ptr2->next = ptr1;
	return (ptr2);
}

int		ft_while_end(t_data **tmp_list)
{
	while ((*tmp_list) && (*tmp_list)->next)
		*tmp_list = (*tmp_list)->next;
	return (1);
}
