/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 12:44:25 by pguitar           #+#    #+#             */
/*   Updated: 2019/06/13 12:44:27 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_construct_flags(t_flag *flags)
{
	(*flags).rr = 0;
	(*flags).r = 0;
	(*flags).a = 0;
	(*flags).t = 0;
	(*flags).l = 0;
	return (1);
}

int	ft_fill_flags(char argv, t_flag *flags)
{
	if (argv == 'R')
		(*flags).rr = 1;
	if (argv == 'r')
		(*flags).r = 1;
	if (argv == 'a')
		(*flags).a = 1;
	if (argv == 't')
		(*flags).t = 1;
	if (argv == 'l')
		(*flags).l = 1;
	return (1);
}

int	ft_flag_error2(char argv)
{
	if (argv != 'l' && argv != 't' && argv != 'R'
		&& argv != 'r' && argv != 'a')
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(argv, 2);
		ft_putchar_fd('\n', 2);
		ft_putendl_fd("usage: ft_ls [-alRrt] [file ...]", 2);
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	ft_flag_error1(char **argv)
{
	if (argv[1][0] == '-' && argv[1][1] == '\0')
	{
		ft_putstr_fd("ft_ls: -: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		argv[1][0] = '\0';
		return (0);
	}
	return (1);
}

int	ft_sum_flags(int argc, char **argv, t_flag *flags)
{
	int i;
	int k;

	i = 1;
	k = 1;
	ft_construct_flags(flags);
	if (ft_flag_error1(argv) == 0)
		return (1);
	while (i < argc && argv[i] && argv[i][0] == '-')
	{
		while (argv[i][k++])
		{
			CHECK(ft_flag_error2(argv[i][k - 1]));
			ft_fill_flags(argv[i][k - 1], flags);
			argv[i][k - 2] = '\0';
			argv[i][k - 1] = '\0';
		}
		k = 1;
		i++;
	}
	return (1);
}
