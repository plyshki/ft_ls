/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguitar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:00:00 by pguitar           #+#    #+#             */
/*   Updated: 2019/07/22 15:00:04 by pguitar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <limits.h>
# include <dirent.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/types.h>

# define CHECK(x) if (!x) return (0);

typedef struct			s_flag
{
	int					rr;
	int					r;
	int					a;
	int					t;
	int					l;
}						t_flag;

typedef struct			s_file
{
	char				*str;
	struct s_file		*next;
}						t_file;

typedef struct			s_direct
{
	char				*str;
	int					sum;
	struct s_direct		*next;
}						t_direct;

typedef struct			s_tmp
{
	char				*str;
	struct s_tmp		*next;
}						t_tmp;

typedef struct			s_data_list
{
	int					print_name;
	int					print_file;
	blkcnt_t			st_blocks;
	mode_t				mode;
	int					nlink;
	int					size;
	int					mtime;
	char				t_p[12];
	char				*time;
	char				*user_name;
	char				*group_name;
	char				*name;
	char				*full_path;
	int					size_link;
	int					size_usr;
	int					size_grp;
	int					size_size;
	struct s_data_list	*next;
}						t_data;

int						ft_sum_flags(int argc, char **argv, t_flag *flags);
int						ft_push_directs(t_direct **begin_list, char *argv);
int						ft_sort_argv(char **argv, int argc, t_flag flags);
int						ft_sort_argv_time(char **argv, int argc);
int						ft_sort_argv_time_1(int *k, int *j, int argc);
int						ft_sort_argv_reverse(char **argv, int argc);
int						ft_push_directs_files(char **argv, int argc,
						t_direct **begin_directs, t_file **begin_files);
int						ft_print_dir(int i, t_direct **d_list);
int						ft_directs_ls(int i, t_direct **d_list,
						t_file **f_list);
int						ft_push_files(t_file **begin_list, char *argv);
int						ft_print_files(t_file **f_list);
int						ft_file_dir_error(int *j, char **argv,
						t_direct **begin_directs, t_file **begin_files);
int						ft_flags_dir_files(t_direct **d_list,
						t_file **f_list, t_flag *flags);
int						ft_help1(t_flag *flags);
int						ft_flag_l(t_data **tmp, int i);
int						ft_ft1(struct dirent *ptr, char **name, char **tmp);
int						ft_ft2(char **name, char *tmp);
int						ft_size_space_nlink(t_data **list, int j, t_data **tmp);
int						ft_size_space_usr(t_data **list, int j, t_data **tmp);
int						ft_size_space_grp(t_data **list, int j, t_data **tmp);
int						ft_size_space_size(t_data **list, int j, t_data **tmp);
int						ft_sort_list_reverse_2(t_data **list,
						t_data **begin, t_data **end, t_data **end_next);
int						ft_sort_list_reverse_1(t_data **list);
int						ft_content_swap(t_data **begin, t_data **end);
int						ft_add_argv_list(char *name, t_data **list);
int						ft_add_file_list(char *name,
						t_data **list, char *fullpath);
int						ft_add_list(char *name, t_data **list, char *fullpath);
int						ft_print_all_1(t_data **list, t_flag *flags, int i);
int						ft_print_name_dir(char *name,
						t_direct **d_list, t_data **list);
int						ft_print_flag_l_1(t_data **list, int i);
int						ft_print_flag_l_1_support(t_data **list,
						t_data **tmp, int i, int *j);
int						ft_print_flag_l_2(t_data **list, t_data **tmp);
int						ft_free_fdir(t_direct **dir, t_file **file);
int						ft_free_lflag_clist(t_data **list);
int						ft_free_clist(t_data **list);
int						ft_type(t_data **list);
int						ft_simple_flags_1(t_flag *flags, char *name,
						DIR **dir, t_data **tmp_list);
int						ft_simple_flags_2(t_data **list, t_data **member,
						t_flag *flags, t_direct **d_list);
int						ft_simple_flags_3(DIR **dir, t_data **list,
						int *j, int i);
int						ft_while_end(t_data **tmp_list);
int						ft_no_printlink(t_data **list, int i,
						int *j, int l_flag);
int						ft_no_printlink_1(t_data **list);
int						ft_closedir(DIR **dir);
int						ft_d_list_1(t_data **list, t_data **tmp_list, int i,
						t_data **end_list);
int						ft_print_space(int *i);
int						ft_fill(int *j, int *k);
char					*ft_strndup(const char *s1, int n);
char					ft_acl(char path[PATH_MAX]);
char					*ft_strstr1(const char *haystack, const char *needle);
t_data					*ft_sort_list(t_data **list);
t_data					*ft_sort_list_time(t_data **list);
t_data					*ft_swap_list(t_data *ptr1, t_data *ptr2);
t_data					*ft_simple_print(t_flag *flags,
						char *name, int *j);

#endif
