/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_display_lcols.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/15 16:46:35 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 18:15:56 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	max(unsigned int a, unsigned int b)
{
	return ((a > b) ? a : b);
}

static void	lcol_pwduid(t_env **env, t_ls *node, t_lcols *c)
{
	if (!getpwuid(node->filestat->st_uid) || !getgrgid(node->filestat->st_gid))
		return ;
	if ((*env)->p.n)
	{
		c->pwduid = max(ft_intlen(node->filestat->st_uid), c->pwduid);
		c->grpuid = max(ft_intlen(node->filestat->st_gid), c->grpuid);
	}
	else
	{
		c->pwduid = max(ft_strlen(getpwuid(node->filestat->st_uid)->pw_name),
															c->pwduid);
		c->grpuid = max(ft_strlen(getgrgid(node->filestat->st_gid)->gr_name),
															c->grpuid);
	}
}

void		lcol_init(t_env **env, t_ls *bt)
{
	t_ls	*tmp;
	t_lcols	*c;

	tmp = bt;
	c = &(*env)->cols;
	c->pwduid = 0;
	c->grpuid = 0;
	c->size = 0;
	c->major = 0;
	c->minor = 0;
	c->lnkcount = 0;
	c->inode = 0;
	while (tmp)
	{
		c->size = max(ft_intlen(tmp->filestat->st_size), c->size);
		lcol_pwduid(env, tmp, c);
		if ((*env)->p.inode)
			c->inode = max(ft_intlen(tmp->filestat->st_ino), c->inode);
		c->major = max(ft_intlen(major(tmp->filestat->st_rdev)), c->major);
		c->minor = max(ft_intlen(minor(tmp->filestat->st_rdev)), c->minor);
		c->lnkcount = max(ft_intlen(tmp->filestat->st_nlink), c->lnkcount);
		tmp = tmp->next;
	}
}
