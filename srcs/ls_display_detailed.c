/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_display_detailed.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 18:44:09 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 18:13:08 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ls_print_inode(t_ls *bt, int col)
{
	ft_printspace(col - ft_intlen(bt->filestat->st_ino));
	ft_putnbr(bt->filestat->st_ino);
	write(1, " ", 1);
}

void	ls_print_countsub(t_ls *bt, int col)
{
	col -= ft_intlen(bt->filestat->st_nlink);
	ft_printspace(col);
	ft_putnbr(bt->filestat->st_nlink);
	write(1, " ", 1);
}

void	ls_print_totalblock(t_ls *bt)
{
	t_ls			*tmp;
	int				total;

	total = 0;
	tmp = bt;
	while (tmp)
	{
		total += tmp->filestat->st_blocks;
		tmp = tmp->next;
	}
	write(1, "total ", 6);
	ft_putnbr(total);
	write(1, "\n", 1);
}

void	ls_print_uid(t_env **env, struct stat *filestat)
{
	struct passwd	*pws;
	struct group	*grp;

	if (!getpwuid(filestat->st_uid) || !getgrgid(filestat->st_gid))
		return ;
	pws = getpwuid(filestat->st_uid);
	grp = getgrgid(filestat->st_gid);
	if (!(*env)->p.n)
	{
		ft_putstr(pws->pw_name);
		ft_printspace((*env)->cols.pwduid - ft_strlen(pws->pw_name) + 2);
		ft_putstr(grp->gr_name);
		ft_printspace((*env)->cols.grpuid - ft_strlen(grp->gr_name) + 2);
	}
	else
	{
		ft_putnbr(filestat->st_uid);
		ft_printspace((*env)->cols.pwduid + 2 - ft_intlen(filestat->st_uid));
		ft_putnbr(filestat->st_gid);
		ft_printspace((*env)->cols.grpuid + 2 - ft_intlen(filestat->st_gid));
	}
}

void	ls_print_date(t_params p, long int timesec)
{
	char	*rtime;
	char	*date;

	rtime = ctime(&timesec);
	if (p.fulltime)
		date = ft_strsub(rtime, 4, 20);
	else
		date = ft_strsub(rtime, 4, 12);
	ft_putstr(date);
	free(date);
	write(1, " ", 1);
	return ;
}
