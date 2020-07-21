/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:11:45 by pguitar           #+#    #+#             */
/*   Updated: 2019/07/22 16:12:56 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_add_argv_list(char *name, t_data **list)
{
	t_data *tmp;
	t_data *help;

	help = *list;
	if (!(tmp = (t_data*)malloc(sizeof(t_data))))
		return (0);
	tmp->next = NULL;
	tmp->print_name = 1;
	tmp->print_file = 0;
	tmp->full_path = NULL;
	tmp->name = name;
	if (help == NULL)
		*list = tmp;
	else
	{
		while (help->next != NULL)
			help = help->next;
		help->next = tmp;
	}
	return (1);
}

int	ft_add_file_list(char *name, t_data **list, char *fullpath)
{
	t_data		*tmp;
	t_data		*help;
	struct stat	buf;

	if (lstat(name, &buf) == -1)
		return (0);
	help = *list;
	if (!(tmp = (t_data*)malloc(sizeof(t_data))))
		return (0);
	tmp->next = NULL;
	tmp->print_name = 0;
	tmp->print_file = 1;
	tmp->name = name;
	tmp->full_path = fullpath;
	tmp->mtime = buf.st_mtime;
	if (help == NULL)
		*list = tmp;
	else
	{
		while (help->next != NULL)
			help = help->next;
		help->next = tmp;
	}
	return (1);
}

int	ft_add_list(char *name, t_data **list, char *fullpath)
{
	t_data		*tmp;
	t_data		*help;
	struct stat	buf;

	help = *list;
	if (lstat(fullpath, &buf) == -1)
		return (0);
	if (!(tmp = (t_data*)malloc(sizeof(t_data))))
		return (0);
	tmp->next = NULL;
	tmp->print_name = 0;
	tmp->print_file = 0;
	tmp->name = name;
	tmp->full_path = fullpath;
	tmp->mtime = buf.st_mtime;
	if (help == NULL)
		*list = tmp;
	else
	{
		while (help->next != NULL)
			help = help->next;
		help->next = tmp;
	}
	return (1);
}

int	ft_closedir(DIR **dir)
{
	if (*dir)
		closedir(*dir);
	return (1);
}

int	ft_d_list_1(t_data **list, t_data **tmp_list, int i, t_data **end_list)
{
	if (i == 1)
		*tmp_list = *list;
	ft_while_end(list);
	*end_list = NULL;
	return (1);
}
