/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:02:05 by pguitar           #+#    #+#             */
/*   Updated: 2019/06/13 14:02:06 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_print_space(int *i)
{
	while (*i > 0)
	{
		(*i)--;
		ft_putchar(' ');
	}
	return (1);
}

char	*ft_slash(char *argv)
{
	int		i;
	char	*str;

	str = argv - 1;
	ft_putstr(str);
	str = ft_strdup(argv);
	i = ft_strlen(str) - 1;
	if (str[i] == '/')
		str[i] = '\0';
	return (str);
}

int		ft_push_directs(t_direct **begin_list, char *argv)
{
	t_direct	*tmp;
	t_direct	*help;
	static int	sum;

	help = *begin_list;
	if (!(tmp = (t_direct*)malloc(sizeof(t_direct))))
		return (0);
	tmp->next = NULL;
	tmp->str = ft_slash(argv);
	tmp->sum = ++sum;
	if (help == NULL)
		*begin_list = tmp;
	else
	{
		while (help->next != NULL)
		{
			help->sum = tmp->sum;
			help = help->next;
		}
		help->next = tmp;
		(*begin_list)->sum = tmp->sum;
	}
	return (1);
}

int		ft_print_dir(int i, t_direct **d_list)
{
	DIR				*dir;
	char			*file;
	struct dirent	*ptr;

	dir = NULL;
	if (!(dir = opendir((*d_list)->str)))
		return (0);
	if (i == 1)
	{
		ft_putstr((*d_list)->str);
		ft_putstr(":\n");
	}
	while ((ptr = readdir(dir)) != NULL)
	{
		if (ptr->d_name[0] == '.')
			continue;
		file = ptr->d_name;
		ft_putstr(file);
		ft_putstr("\n");
	}
	closedir(dir);
	if ((*d_list = (*d_list)->next))
		ft_putstr("\n");
	return (1);
}

int		ft_directs_ls(int i, t_direct **d_list, t_file **f_list)
{
	if (*f_list != NULL)
	{
		CHECK(ft_print_files(f_list));
		if (*d_list)
			ft_putstr("\n");
	}
	while (*d_list)
	{
		if (*d_list != NULL)
			CHECK(ft_print_dir(i, d_list));
	}
	return (1);
}
