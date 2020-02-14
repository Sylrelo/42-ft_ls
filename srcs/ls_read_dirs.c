/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_read_dirs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 10:10:04 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/21 16:35:26 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_recursion(t_env **env, t_ls *ls)
{
	t_ls	*tmp;

	tmp = ls;
	while (tmp)
	{
		if (!S_ISLNK(tmp->filestat->st_mode) && S_ISDIR(tmp->filestat->st_mode)
			&& (*env)->p.recur && !ft_file_isspecial(tmp->dname))
		{
			(*env)->count++;
			ls_readdir(tmp->name, env, tmp->right, NULL);
		}
		tmp = tmp->next;
	}
}

static void	ls_print_dirname(t_env **env, char *cdir)
{
	if ((*env)->count > 0)
	{
		write(1, "\n", 1);
		ft_putstr(cdir);
		write(1, ":\n", 2);
	}
}

static DIR	*ls_rd_init(t_checks *chk, char *cdir)
{
	char			*str;
	DIR				*dd;

	if (ls_list_check(chk, cdir))
		return (NULL);
	dd = opendir(cdir);
	if (!dd)
	{
		if ((str = ft_strrchr(cdir, '/')))
		{
			ft_putstr("ft_ls: ");
			perror(&str[1]);
		}
		return (NULL);
	}
	return (dd);
}

int			ls_readdir(char *cdir, t_env **env, t_ls *bt, t_checks *chk)
{
	DIR				*dd;
	struct dirent	*dent;

	if (!(dd = ls_rd_init(chk, cdir)))
		return (0);
	while ((dent = readdir(dd)) != NULL)
		if (ft_file_ishidden(dent->d_name) && (*env)->p.a)
			ls_list_insert(*env, &bt, dent, cdir);
		else if (!ft_file_ishidden(dent->d_name))
			ls_list_insert(*env, &bt, dent, cdir);
	if ((*env)->p.r)
		ls_reverse(&bt);
	ls_print_dirname(env, cdir);
	ls_display(env, bt);
	closedir(dd);
	ls_free_readdirs(bt);
	ft_memdel((void **)&dent);
	return (1);
}
