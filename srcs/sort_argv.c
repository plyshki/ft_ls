/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:52:47 by pguitar           #+#    #+#             */
/*   Updated: 2019/08/09 15:52:49 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_sort_argv_time(char **argv, int argc)
{
	int			j;
	int			k;
	char		*tmp;
	struct stat	buf1;
	struct stat	buf2;

	ft_fill(&j, &k);
	while (k < argc)
	{
		if (argv[j][0] == '\0' && k++ && j++)
			continue;
		if (lstat(argv[j], &buf1) == -1)
			return (0);
		if (lstat(argv[k], &buf2) == -1)
			return (0);
		if (buf1.st_mtime < buf2.st_mtime)
		{
			tmp = argv[j];
			argv[j] = argv[k];
			argv[k] = tmp;
		}
		ft_sort_argv_time_1(&k, &j, argc);
		k++;
	}
	return (1);
}

int	ft_sort_argv_reverse(char **argv, int argc)
{
	int		j;
	int		k;
	int		p;
	char	*tmp;

	j = 1;
	k = 1;
	p = 0;
	while (p != j)
	{
		if (j >= argc)
			break ;
		if (argv[j][0] == '\0' && j++)
			continue;
		tmp = argv[j];
		p = argc - k;
		if (p == j)
			break ;
		argv[j] = argv[p];
		argv[p] = tmp;
		k++;
		j++;
	}
	return (1);
}

int	ft_sort_argv(char **argv, int argc, t_flag flags)
{
	int		j;
	int		k;
	char	*tmp;

	ft_fill(&j, &k);
	while (k < argc)
	{
		if (ft_strcmp(argv[j], argv[k]) > 0)
		{
			tmp = argv[j];
			argv[j] = argv[k];
			argv[k] = tmp;
		}
		if (k == argc - 1)
		{
			j++;
			k = j;
		}
		k++;
	}
	if (flags.t)
		ft_sort_argv_time(argv, argc);
	if (flags.r)
		ft_sort_argv_reverse(argv, argc);
	return (1);
}

int	ft_no_printlink_1(t_data **list)
{
	char *tmp;

	if ((*list)->full_path == NULL)
		tmp = (*list)->name;
	else
		tmp = (*list)->full_path;
	(*list) = (*list)->next;
	while (*list)
	{
		if ((*list)->print_name == 1 && ft_strstr1((*list)->name, tmp) == 0)
			break ;
		(*list) = (*list)->next;
	}
	return (1);
}

int	ft_no_printlink(t_data **list, int i, int *j, int l_flag)
{
	struct stat	buf;
	static int	k;

	if (lstat((*list)->name, &buf) == -1)
		return (0);
	if (S_ISLNK(buf.st_mode))
	{
		ft_no_printlink_1(list);
		return (1);
	}
	if (i == 1 && k == 0)
	{
		if (l_flag == 1)
		{
			ft_putstr("total ");
			ft_putnbr((*list)->st_blocks);
			ft_putstr("\n");
		}
		k = 1;
		(*j)++;
		(*list) = (*list)->next;
		return (1);
	}
	return (0);
}
