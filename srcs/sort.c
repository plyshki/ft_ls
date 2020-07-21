/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:00:35 by pguitar           #+#    #+#             */
/*   Updated: 2019/07/22 15:00:40 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_content_swap(t_data **begin, t_data **end)
{
	int		tmp_int;
	char	*tmp;

	tmp = (*begin)->name;
	(*begin)->name = (*end)->name;
	(*end)->name = tmp;
	tmp = (*begin)->full_path;
	(*begin)->full_path = (*end)->full_path;
	(*end)->full_path = tmp;
	tmp_int = (*begin)->mtime;
	(*begin)->mtime = (*end)->mtime;
	(*end)->mtime = tmp_int;
	return (1);
}

int		ft_sort_list_reverse_2(t_data **list, t_data **begin, t_data **end,
		t_data **end_next)
{
	t_data *hpt;

	while ((*end) && (*end)->next && (*end)->next->print_name == 0)
		(*end) = (*end)->next;
	(*end_next) = (*end)->next;
	while ((*begin) != (*end))
	{
		ft_content_swap(begin, end);
		(*begin) = (*begin)->next;
		if ((*begin) == (*end))
			break ;
		hpt = (*begin);
		while (hpt->next != (*end) && (*end) != *list)
			hpt = hpt->next;
		(*end) = hpt;
	}
	return (1);
}

int		ft_sort_list_reverse_1(t_data **list)
{
	t_data *begin;
	t_data *end;
	t_data *end_next;

	begin = *list;
	if (!(*list))
		return (1);
	while (begin && begin->next &&
	(begin->print_name == 1 || begin->next->print_name == 1))
		begin = begin->next;
	if (!begin)
		return (1);
	end = begin;
	ft_sort_list_reverse_2(list, &begin, &end, &end_next);
	ft_sort_list_reverse_1(&end_next);
	return (1);
}

t_data	*ft_sort_list_time(t_data **list)
{
	if (!(*list))
		return (NULL);
	if ((*list)->next && (*list)->print_name == 0 &&
			(*list)->next->print_name == 0
			&& (*list)->mtime < (*list)->next->mtime)
		(*list) = ft_swap_list((*list), (*list)->next);
	(*list)->next = ft_sort_list_time(&((*list)->next));
	if ((*list)->next && (*list)->print_name == 0 &&
			(*list)->next->print_name == 0
			&& (*list)->mtime < (*list)->next->mtime)
	{
		(*list) = ft_swap_list((*list), (*list)->next);
		(*list)->next = ft_sort_list_time(&((*list)->next));
	}
	return ((*list));
}

t_data	*ft_sort_list(t_data **list)
{
	if (!(*list))
		return (NULL);
	if ((*list)->next && (*list)->print_name == 0 &&
			(*list)->next->print_name == 0
			&& ft_strcmp((*list)->name, (*list)->next->name) > 0)
		(*list) = ft_swap_list((*list), (*list)->next);
	(*list)->next = ft_sort_list(&((*list)->next));
	if ((*list)->next && (*list)->print_name == 0 &&
			(*list)->next->print_name == 0
			&& ft_strcmp((*list)->name, (*list)->next->name) > 0)
	{
		(*list) = ft_swap_list((*list), (*list)->next);
		(*list)->next = ft_sort_list(&((*list)->next));
	}
	return ((*list));
}
