/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_read_files.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 17:05:53 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/08/21 16:35:28 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static	int	ls_rf_getstats(t_dirlist *tmp, struct stat *filestat)
{
	if (lstat(tmp->name, filestat) < 0)
	{
		if (stat(tmp->name, filestat) < 0)
		{
			ft_putstr("ft_ls: ");
			perror(tmp->name);
			return (1);
		}
	}
	return (0);
}

static int	ls_rf_continue(t_env **env, int count, struct stat *filestat)
{
	if (!count)
	{
		free(filestat);
		return (0);
	}
	(*env)->isfile = 1;
	ls_display(env, (*env)->ls);
	ls_free_readfiles((*env)->ls);
	free(filestat);
	(*env)->isfile = 0;
	return (1);
}

int			ls_solofiles(t_env **env, t_checks **chk)
{
	t_dirlist		*tmp;
	struct stat		*filestat;
	int				count;
	int				err;

	if (!(filestat = malloc(sizeof(*filestat))))
		p_error('m');
	tmp = (*env)->dirs;
	count = 0;
	while (tmp)
	{
		err = ls_rf_getstats(tmp, filestat);
		if (!err && !S_ISDIR(filestat->st_mode) && !(S_ISLNK(filestat->st_mode)
			&& !(*env)->p.l) && !(*env)->p.symbolicfollow)
		{
			ls_list_fileinsert(*env, filestat, tmp->name);
			ls_list_insert_check(chk, tmp->name);
			count += 1;
		}
		if (err)
			ls_list_insert_check(chk, tmp->name);
		tmp = tmp->next;
	}
	return (ls_rf_continue(env, count, filestat));
}
