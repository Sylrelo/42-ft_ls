/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_listutils.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 12:23:12 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 16:16:27 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ls_list_insert_check(t_checks **head, char *path)
{
	t_checks	*newl;

	if (!(newl = (t_checks *)malloc(sizeof(t_checks))))
		p_error('m');
	ft_strcpy(newl->path, path);
	newl->next = *head;
	*head = newl;
	return ;
}

int				ls_list_check(t_checks *head, char *path)
{
	t_checks	*tmp;

	if (!head)
		return (0);
	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->path, path) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void			ls_list_insert(t_env *env, t_ls **head, \
								struct dirent *dent, char *cdir)
{
	t_ls	*lst;

	if (!(lst = (t_ls *)malloc(sizeof(t_ls))))
		p_error('m');
	lst->dent = dent;
	ft_strcpy(lst->dname, lst->dent->d_name);
	lst->dtype = dent->d_type;
	ft_strcpy(lst->name, cdir);
	ft_strcat(lst->name, "/");
	ft_strcat(lst->name, lst->dent->d_name);
	lst->right = NULL;
	lst->filestat = ls_get_filestat(lst);
	lst->timesec = ls_handletime(env, lst->filestat);
	ls_list_insert_sort(env, head, lst);
}

void			ls_list_fileinsert(t_env *env, struct stat *filestat, \
									char *fname)
{
	t_ls			*lst;
	struct stat		*fs;

	if (!(fs = malloc(sizeof(*fs))))
		p_error('m');
	if (lstat(fname, fs) < 0)
		if (stat(fname, fs) < 0)
		{
			ft_putstr("./ft_ls: ");
			perror(fname);
			exit(1);
		}
	if (!(lst = (t_ls *)malloc(sizeof(t_ls))))
		p_error('m');
	lst->dent = NULL;
	ft_strcpy(lst->dname, fname);
	lst->dtype = ls_file_type(filestat);
	ft_strcpy(lst->name, fname);
	lst->right = NULL;
	lst->filestat = fs;
	lst->timesec = ls_handletime(env, lst->filestat);
	ls_list_insert_sort(env, &env->ls, lst);
}
