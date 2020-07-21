/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:39:08 by pguitar           #+#    #+#             */
/*   Updated: 2019/06/13 16:39:09 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_sort_argv_time_1(int *k, int *j, int argc)
{
	if (*k == argc - 1)
	{
		(*j)++;
		*k = *j;
	}
	return (1);
}

int		ft_print_files(t_file **f_list)
{
	int i;

	i = 0;
	while (*f_list)
	{
		ft_putstr((*f_list)->str);
		ft_putstr("\n");
		i++;
		(*f_list) = (*f_list)->next;
	}
	return (1);
}

int		ft_push_files(t_file **begin_list, char *argv)
{
	t_file *tmp;
	t_file *help;

	help = *begin_list;
	if (!(tmp = (t_file*)malloc(sizeof(t_file))))
		return (0);
	tmp->next = NULL;
	tmp->str = argv;
	if (help == NULL)
		*begin_list = tmp;
	else
	{
		while (help->next != NULL)
			help = help->next;
		help->next = tmp;
	}
	return (1);
}

int		ft_file_dir_error(int *j, char **argv, t_direct **begin_directs,
		t_file **begin_files)
{
	static int	i;
	DIR			*dir;
	struct stat	buf;

	dir = NULL;
	if (!(argv[*j][0] == '\0' && argv[*j][1] == '\0'))
	{
		if ((dir = opendir(argv[*j])))
		{
			CHECK(ft_push_directs(begin_directs, argv[*j]));
			closedir(dir);
		}
		else if ((lstat(argv[*j], &buf) == 0))
		{
			CHECK(ft_push_files(begin_files, argv[*j]));
		}
		else
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(argv[*j], 2);
			ft_putendl_fd(": No such file or directory", 2);
			i = 1;
		}
	}
	return (i);
}

char	*ft_strstr1(const char *haystack, const char *needle)
{
	const char	*ptr;
	size_t		len;

	len = ft_strlen(needle);
	ptr = haystack;
	if (*needle == '\0')
		return (char *)ptr;
	while ((ptr = ft_strchr(ptr, *needle)) != 0)
	{
		if (ft_strncmp(ptr, needle, len) == 0 &&
		(ptr[len] == '/' || ptr[len] == '\0'))
			return (char *)ptr;
		ptr++;
	}
	return (0);
}
