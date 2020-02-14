/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/22 11:00:57 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 18:30:51 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ls_free_readdirs(t_ls *head)
{
	if (!head)
		return ;
	free(head->filestat);
	ls_free_readdirs(head->right);
	ls_free_readdirs(head->next);
	ft_memdel((void **)&head);
}

void	ls_free_readfiles(t_ls *bt)
{
	t_ls *t;
	t_ls *tmp;

	t = bt;
	if (!bt)
		return ;
	while (bt)
	{
		tmp = bt->next;
		free(bt->filestat);
		free(bt);
		bt = tmp;
	}
	free(bt);
	bt = NULL;
}

void	ls_free_chk(t_checks *chk)
{
	t_checks *tmp;

	while (chk)
	{
		tmp = chk->next;
		ft_memdel((void **)&chk);
		chk = tmp;
	}
	ft_memdel((void **)&chk);
}

void	ls_free_all(t_env *env)
{
	t_dirlist	*tmp;
	int			i;

	i = 0;
	while (env->dirs)
	{
		tmp = env->dirs->next;
		ft_memdel((void **)&env->dirs);
		env->dirs = tmp;
		i++;
	}
	if (i > 0)
	{
		ft_memdel((void **)&env->dirs);
		ft_memdel((void **)&tmp);
	}
	ft_memdel((void **)&env);
}
