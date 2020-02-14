/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_display.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 16:23:18 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 18:43:53 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	ls_print_name(t_params p, t_ls *ls, char *name)
{
	if (!p.color)
	{
		ft_putstr(name);
		return ;
	}
	if (ls->dtype == DT_DIR)
		ft_putstr("\033[1;36m");
	if (ls->dtype == DT_LNK)
		ft_putstr("\033[1;35m");
	else if (ls->dtype == DT_CHR)
		ft_putstr("\033[1;43m");
	else if (ls->dtype == DT_BLK)
		ft_putstr("\033[1;46m");
	if (ls->filestat->st_mode & S_IXUSR && !(ls->dtype == DT_DIR) && \
		!(ls->dtype == DT_LNK))
		ft_putstr("\033[1;31m");
	if (ls->filestat->st_mode & S_ISGID)
		ft_putstr("\033[1;46m\033[1;37m");
	if (ls->filestat->st_mode & S_ISUID)
		ft_putstr("\033[1;41m\033[1;37m");
	ft_putstr(name);
	ft_putstr("\033[0;m");
}

static void	ls_display_l(t_env **env, t_ls *bt)
{
	if ((*env)->p.inode)
		ls_print_inode(bt, (*env)->cols.inode);
	ls_print_perms(bt);
	ls_print_countsub(bt, (*env)->cols.lnkcount);
	ls_print_uid(env, bt->filestat);
	if (bt->dtype == DT_CHR || bt->dtype == DT_BLK)
		ls_print_minormajor(bt, (*env)->cols);
	else if ((*env)->p.h)
		ls_print_size_human(bt->filestat);
	else
		ls_print_size(bt->filestat, (*env)->cols.size);
	ls_print_date((*env)->p, bt->timesec);
	ls_print_name((*env)->p, bt, bt->dname);
	ls_print_symbolic_origin(bt);
	write(1, "\n", 1);
}

static void	ls_display_std(t_env **env, t_ls *tmp)
{
	ls_print_name((*env)->p, tmp, tmp->dname);
	ft_putchar('\n');
}

void		ls_display(t_env **env, t_ls *bt)
{
	t_ls	*tmp;

	if (!bt)
		return ;
	if ((*env)->p.l && bt)
		lcol_init(env, bt);
	tmp = bt;
	if (!tmp)
		return ;
	if ((*env)->isfile != 1 && (*env)->p.l)
		ls_print_totalblock(bt);
	while (tmp)
	{
		if ((*env)->p.l)
			ls_display_l(env, tmp);
		else
			ls_display_std(env, tmp);
		tmp = tmp->next;
	}
	ls_recursion(env, bt);
}
