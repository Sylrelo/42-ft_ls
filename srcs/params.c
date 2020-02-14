/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   params.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 18:46:44 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 16:08:59 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		opt_dirs_push(t_dirlist **head, char *c)
{
	t_dirlist	*new;
	t_dirlist	*tmp;

	if (!(new = (t_dirlist *)malloc(sizeof(t_dirlist))))
		p_error('m');
	new->name = c;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void		opt_params_edit(t_env *env, char c)
{
	env->p.r = (c == 'r' ? 1 : env->p.r);
	env->p.recur = (c == 'R' ? 1 : env->p.recur);
	env->p.a = (c == 'a' ? 1 : env->p.a);
	env->p.t = (c == 't' ? 1 : env->p.t);
	env->p.l = (c == 'l' ? 1 : env->p.l);
	env->p.color = (c == 'G' ? 1 : env->p.color);
	env->p.h = (c == 'h' ? 1 : env->p.h);
	env->p.symbolicfollow = (c == 'H' ? 1 : env->p.symbolicfollow);
	env->p.inode = (c == 'i' ? 1 : env->p.inode);
	env->p.n = (c == 'n' ? 1 : env->p.n);
	env->p.fulltime = (c == 'T' ? 1 : env->p.fulltime);
	env->p.sortsize = (c == 'S' ? 1 : env->p.sortsize);
	env->p.creationdate = (c == 'U' ? 1 : env->p.creationdate);
	env->p.lastaccess = (c == 'u' ? 1 : env->p.lastaccess);
}

static void		opt_params_handle(t_env *env, char *c)
{
	int		i;

	i = 0;
	while (c[i])
	{
		if (c[i] == '-')
			i++;
		if (!(ft_strchr(VALID_OPTS, c[i])))
			error_invalid_options(&c[i]);
		opt_params_edit(env, c[i]);
		i++;
	}
}

void			opt_handle(t_env *env, char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-' && !argv[i][1])
			break ;
		else if (argv[i][0] == '-' && argv[i][1] != '-')
			opt_params_handle(env, argv[i]);
		else if (argv[i][0] == '-' && argv[i][1] == '-')
		{
			i++;
			break ;
		}
		else
			break ;
		i++;
	}
	if (argv[i])
		while (argv[i])
		{
			opt_dirs_push(&(env->dirs), argv[i++]);
			env->count++;
		}
}
