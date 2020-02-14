/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_tools.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 17:35:24 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 16:17:14 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_sort_swap(t_ls **prev, t_ls **curr)
{
	*prev = (*curr);
	*curr = (*curr)->next;
}

struct stat	*ls_get_filestat(t_ls *bt)
{
	struct stat *filestat;

	if (!(filestat = malloc(sizeof(*filestat))))
		p_error('m');
	if (lstat(bt->name, filestat) < 0)
		if (stat(bt->name, filestat) < 0)
		{
			perror(bt->name);
			ft_error("\n/ft_ls : an error occured. [filestat fail]");
		}
	return (filestat);
}

long int	ls_handletime(t_env *env, struct stat *stat)
{
	if (env->p.lastaccess)
		return (stat->st_atimespec.tv_sec);
	else if (env->p.creationdate)
		return (stat->st_birthtimespec.tv_sec);
	else
		return (stat->st_mtimespec.tv_sec);
}

int			ls_file_type(struct stat *filestat)
{
	int	md;

	md = filestat->st_mode;
	if (S_ISDIR(md))
		return (4);
	if (S_ISFIFO(md))
		return (1);
	if (S_ISREG(md))
		return (8);
	if (S_ISCHR(md))
		return (2);
	if (S_ISBLK(md))
		return (6);
	if (S_ISLNK(md))
		return (10);
	if (S_ISSOCK(md))
		return (12);
	return (0);
}
