/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 18:18:39 by pguitar           #+#    #+#             */
/*   Updated: 2019/06/18 18:18:40 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_help1(t_flag *flags)
{
	if ((*flags).rr == 1 || (*flags).r == 1 || (*flags).a == 1
		|| (*flags).t == 1 || (*flags).l == 1)
		return (1);
	return (0);
}

int		ft_ft1(struct dirent *ptr, char **name, char **tmp)
{
	char *str;

	*tmp = ft_strdup(*name);
	str = ft_strjoin(*name, "/");
	*name = ft_strjoin(str, ptr->d_name);
	free(str);
	return (1);
}

int		ft_ft2(char **name, char *tmp)
{
	ft_strdel(name);
	*name = tmp;
	return (1);
}

int		ft_type(t_data **list)
{
	(*list)->mode = ((*list)->mode & S_IFMT);
	if (S_ISREG((*list)->mode))
		(*list)->t_p[0] = '-';
	else if (S_ISDIR((*list)->mode))
		(*list)->t_p[0] = 'd';
	else if (S_ISLNK((*list)->mode))
		(*list)->t_p[0] = 'l';
	else if (S_ISBLK((*list)->mode))
		(*list)->t_p[0] = 'b';
	else if (S_ISCHR((*list)->mode))
		(*list)->t_p[0] = 'c';
	else if (S_ISSOCK((*list)->mode))
		(*list)->t_p[0] = 's';
	else if (S_ISFIFO((*list)->mode))
		(*list)->t_p[0] = 'p';
	else
		(*list)->t_p[0] = '-';
	return (1);
}

char	ft_acl(char path[PATH_MAX])
{
	acl_t	tmp;
	char	buf[101];

	if (listxattr(path, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}
