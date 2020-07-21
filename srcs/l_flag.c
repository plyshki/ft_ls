/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:19:02 by pguitar           #+#    #+#             */
/*   Updated: 2019/07/22 16:19:08 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_type_permit_2(t_data **list, struct stat *buf)
{
	if ((*buf).st_mode & S_IWGRP)
		(*list)->t_p[5] = 'w';
	else
		(*list)->t_p[5] = '-';
	if ((*buf).st_mode & S_IXGRP)
		(*list)->t_p[6] = 'x';
	else
		(*list)->t_p[6] = '-';
	if ((*buf).st_mode & S_IROTH)
		(*list)->t_p[7] = 'r';
	else
		(*list)->t_p[7] = '-';
	if ((*buf).st_mode & S_IWOTH)
		(*list)->t_p[8] = 'w';
	else
		(*list)->t_p[8] = '-';
	if ((*buf).st_mode & S_IXOTH)
		(*list)->t_p[9] = 'x';
	else
		(*list)->t_p[9] = '-';
	(*list)->t_p[10] = ft_acl((*list)->full_path);
	(*list)->t_p[11] = '\0';
	return (1);
}

int	ft_type_permit_1(t_data **list, struct stat *buf)
{
	ft_type(list);
	if ((*buf).st_mode & S_IRUSR)
		(*list)->t_p[1] = 'r';
	else
		(*list)->t_p[1] = '-';
	if ((*buf).st_mode & S_IWUSR)
		(*list)->t_p[2] = 'w';
	else
		(*list)->t_p[2] = '-';
	if ((*buf).st_mode & S_IXUSR)
		(*list)->t_p[3] = 'x';
	else
		(*list)->t_p[3] = '-';
	if ((*buf).st_mode & S_IRGRP)
		(*list)->t_p[4] = 'r';
	else
		(*list)->t_p[4] = '-';
	ft_type_permit_2(list, buf);
	return (1);
}

int	ft_flag_l_help(struct stat *buf, t_data **list, t_data **tmp)
{
	(*list)->mode = (*buf).st_mode;
	ft_type_permit_1(list, buf);
	(*list)->nlink = (*buf).st_nlink;
	(*list)->user_name = ft_strdup(getpwuid((*buf).st_uid)->pw_name);
	(*list)->group_name = ft_strdup(getgrgid((*buf).st_gid)->gr_name);
	(*list)->size = (*buf).st_size;
	ft_size_space_nlink(list, 0, tmp);
	ft_size_space_usr(list, 0, tmp);
	ft_size_space_grp(list, 0, tmp);
	ft_size_space_size(list, 0, tmp);
	(*list)->time = ft_strndup(ctime(&((*buf).st_mtime)) + 4, 12);
	return (0);
}

int	ft_flag_l_1(t_data **lll, struct stat *buf, t_data **tmp)
{
	static int j;

	if ((*lll)->print_name == 0)
	{
		if (lstat((*lll)->full_path, buf) == -1)
			return (0);
		(*lll)->st_blocks = (*buf).st_blocks;
		j = j + (*lll)->st_blocks;
		ft_flag_l_help(buf, lll, tmp);
		(*lll) = (*lll)->next;
	}
	else
	{
		(*tmp)->st_blocks = j;
		ft_size_space_nlink(lll, 2, tmp);
		ft_size_space_usr(lll, 2, tmp);
		ft_size_space_grp(lll, 2, tmp);
		ft_size_space_size(lll, 2, tmp);
		j = 0;
		(*tmp) = (*lll);
		(*tmp)->size_size = 0;
		(*tmp)->size_link = 0;
		(*lll) = (*lll)->next;
	}
	return (j);
}

int	ft_flag_l(t_data **list, int i)
{
	int			j;
	t_data		*lll;
	t_data		*tmp;
	struct stat	buf;

	j = 0;
	lll = *list;
	tmp = *list;
	while (lll)
		j = ft_flag_l_1(&lll, &buf, &tmp);
	tmp->st_blocks = j;
	ft_print_flag_l_1(list, i);
	return (1);
}
