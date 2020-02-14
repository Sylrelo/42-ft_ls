/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 18:45:02 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 16:08:32 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	init_options(t_env *env)
{
	env->p.r = 0;
	env->p.recur = 0;
	env->p.a = 0;
	env->p.t = 0;
	env->p.l = 0;
	env->p.color = 0;
	env->p.h = 0;
	env->p.symbolicfollow = 0;
	env->p.inode = 0;
	env->p.n = 0;
	env->p.fulltime = 0;
	env->p.sortsize = 0;
	env->p.lastaccess = 0;
	env->p.creationdate = 0;
}

static void	init_struct(t_env *env, char *argv[])
{
	env->dirs = NULL;
	env->ls = NULL;
	env->count = 0;
	env->isfile = 0;
	init_options(env);
	opt_handle(env, argv);
}

int			main(int argc, char *argv[])
{
	t_env		*env;
	t_dirlist	*tmp;
	t_checks	*chk;

	(void)argc;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		p_error('m');
	init_struct(env, argv);
	chk = NULL;
	tmp = env->dirs;
	if (!env->dirs)
		ls_readdir(".", &env, env->ls, chk);
	else
	{
		env->count += ls_solofiles(&env, &chk);
		env->ls = NULL;
		while (tmp)
		{
			ls_readdir(tmp->name, &env, env->ls, chk);
			tmp = tmp->next;
		}
	}
	ls_free_all(env);
	ls_free_chk(chk);
	return (0);
}
