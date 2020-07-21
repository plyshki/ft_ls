/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:56:43 by pguitar           #+#    #+#             */
/*   Updated: 2019/06/06 14:56:47 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*ft_swap_simple_ls(t_file *ptr1, t_file *ptr2)
{
	ptr1->next = ptr2->next;
	ptr2->next = ptr1;
	return (ptr2);
}

t_file	*ft_sort_simple_ls(t_file **files)
{
	if (!(*files))
		return (NULL);
	if ((*files)->next &&
		ft_strcmp((*files)->str, (*files)->next->str) > 0)
		(*files) = ft_swap_simple_ls((*files), (*files)->next);
	(*files)->next = ft_sort_simple_ls(&((*files)->next));
	if ((*files)->next &&
		ft_strcmp((*files)->str, (*files)->next->str) > 0)
	{
		(*files) = ft_swap_simple_ls((*files), (*files)->next);
		(*files)->next = ft_sort_simple_ls(&((*files)->next));
	}
	return ((*files));
}

int		ft_simple_ls(t_file **begin_files)
{
	DIR				*dir;
	t_file			*tmp;
	struct dirent	*ptr;

	CHECK((dir = opendir(".")));
	while ((ptr = readdir(dir)) != NULL)
	{
		if (ptr->d_name[0] == '.')
			continue;
		CHECK(ft_push_files(begin_files, ft_strdup(ptr->d_name)));
	}
	(*begin_files) = ft_sort_simple_ls(begin_files);
	while (*begin_files)
	{
		ft_putstr((*begin_files)->str);
		ft_putstr("\n");
		tmp = (*begin_files)->next;
		free((*begin_files)->str);
		free(*begin_files);
		*begin_files = tmp;
	}
	closedir(dir);
	return (1);
}

int		ft_ls(int argc, char **argv, t_direct **begin_directs,
		t_file **begin_files)
{
	int			i;
	t_flag		flags;
	t_direct	*tmp_dir;
	t_file		*tmp_file;

	i = 0;
	if (argc == 1)
	{
		CHECK(ft_simple_ls(begin_files));
		return (1);
	}
	CHECK(ft_sum_flags(argc, argv, &flags));
	ft_sort_argv(argv, argc, flags);
	CHECK(ft_push_directs_files(argv, argc, begin_directs, begin_files));
	tmp_dir = (*begin_directs);
	tmp_file = (*begin_files);
	if (argc > 2 && !(ft_help1(&flags)))
		i = 1;
	if (!(ft_help1(&flags)))
		CHECK(ft_directs_ls(i, &tmp_dir, &tmp_file));
	if (ft_help1(&flags))
		CHECK(ft_flags_dir_files(&tmp_dir, &tmp_file, &flags));
	return (1);
}

int		main(int argc, char **argv)
{
	t_file		*begin_files;
	t_direct	*begin_directs;

	begin_files = NULL;
	begin_directs = NULL;
	ft_ls(argc, argv, &begin_directs, &begin_files);
	ft_free_fdir(&begin_directs, &begin_files);
	return (1);
}
