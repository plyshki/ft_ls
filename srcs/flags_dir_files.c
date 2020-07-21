/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_dir_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 15:48:11 by pguitar           #+#    #+#             */
/*   Updated: 2019/06/15 15:48:12 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_push_directs_files(char **argv, int argc, t_direct **begin_directs,
		t_file **begin_files)
{
	int i;
	int j;

	j = 1;
	i = 0;
	while (j < argc)
	{
		i = ft_file_dir_error(&j, argv, begin_directs, begin_files);
		j++;
	}
	if (i == 1 && !(*begin_directs) && !(*begin_files))
		return (0);
	return (1);
}

int		ft_support(DIR **dir, char *name, t_direct **d_list, t_data **list)
{
	ft_print_name_dir(name, d_list, list);
	if (!((*dir) = opendir(name)))
		return (0);
	return (1);
}

t_data	*ft_simple_flags(t_flag *flags, char *name, t_direct **d_list,
		t_data **list)
{
	int		j;
	t_data	*member;
	DIR		*dir;
	t_data	*tmp_list;

	CHECK(ft_support(&dir, name, d_list, list));
	j = ft_simple_flags_1(flags, name, &dir, list);
	if (ft_simple_flags_2(list, &member, flags, d_list) && (*flags).rr == 0)
		return (member);
	while (*list)
	{
		if (ft_simple_flags_3(&dir, list, &j, 1))
			return (member);
		if (ft_simple_flags_3(&dir, list, &j, 2))
			;
		else if ((*list)->print_name == 0 &&
		(dir = opendir((*list)->full_path)))
		{
			tmp_list = *list;
			ft_simple_flags(flags, (*list)->full_path, d_list, &tmp_list);
		}
		*list = (*list)->next;
	}
	ft_closedir(&dir);
	return (member);
}

int		ft_d_list(t_direct **d_list, t_data **list, t_flag *flags)
{
	int		i;
	t_data	*tmp_list;
	t_data	*end_list;

	i = 0;
	end_list = NULL;
	while (*d_list)
	{
		if (++i && *list)
		{
			ft_d_list_1(list, &tmp_list, i, &end_list);
			CHECK(((*list)->next = ft_simple_flags(flags, ((*d_list)->str),
			d_list, &end_list)));
		}
		else
		{
			CHECK((*list = ft_simple_flags(flags, ((*d_list)->str),
			d_list, &end_list)));
			tmp_list = *list;
		}
		*d_list = (*d_list)->next;
		if (!(*d_list))
			*list = tmp_list;
	}
	return (i);
}

int		ft_flags_dir_files(t_direct **d_list, t_file **f_list, t_flag *flags)
{
	int		i;
	t_data	*list;

	i = 0;
	list = NULL;
	if (!(*d_list) && !(*f_list))
		CHECK((list = ft_simple_flags(flags, ".", d_list, &list)));
	while (*f_list)
	{
		i++;
		ft_add_file_list(ft_strdup((*f_list)->str), &list,
				ft_strdup((*f_list)->str));
		*f_list = (*f_list)->next;
	}
	i = i + ft_d_list(d_list, &list, flags);
	ft_print_all_1(&list, flags, i);
	if (list && flags->l == 1)
		ft_free_lflag_clist(&list);
	else
		ft_free_clist(&list);
	return (1);
}
