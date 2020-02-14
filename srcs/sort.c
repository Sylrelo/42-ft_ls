/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 19:05:15 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 12:56:22 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ls_reverse(t_ls **head)
{
	t_ls	*lprev;
	t_ls	*lcurr;
	t_ls	*lnext;

	lprev = NULL;
	lnext = NULL;
	lcurr = *head;
	while (lcurr)
	{
		lnext = lcurr->next;
		lcurr->next = lprev;
		lprev = lcurr;
		lcurr = lnext;
	}
	*head = lprev;
}

static t_ls	*ls_sort_time(t_ls **prev, t_ls **head, t_ls *newl)
{
	t_ls		*curr;
	long int	new_time;

	new_time = newl->timesec;
	curr = *head;
	while (curr != NULL && curr->timesec > new_time)
		ls_sort_swap(prev, &curr);
	while (curr != NULL && curr->timesec == new_time
								&& ft_strcmp(curr->dname, newl->dname) < 0)
		ls_sort_swap(prev, &curr);
	return (curr);
}

static t_ls	*ls_sort_size(t_ls **prev, t_ls **head, t_ls *newl)
{
	t_ls		*curr;
	long int	new_size;

	new_size = newl->filestat->st_size;
	curr = *head;
	while (curr != NULL && curr->filestat->st_size > new_size)
		ls_sort_swap(prev, &curr);
	return (curr);
}

void		ls_list_insert_sort(t_env *env, t_ls **head, t_ls *newl)
{
	t_ls	*curr;
	t_ls	*prev;

	curr = *head;
	prev = NULL;
	if (!newl->filestat)
		ft_error("/ft_ls : an error occured. [filestat fail]");
	if ((env)->p.t)
		curr = ls_sort_time(&prev, head, newl);
	else if ((env)->p.sortsize)
		curr = ls_sort_size(&prev, head, newl);
	else
		while (curr != NULL && ft_strcmp(curr->dname, newl->dname) < 0)
			ls_sort_swap(&prev, &curr);
	newl->next = curr;
	if (prev == NULL)
		*head = newl;
	else
		prev->next = newl;
}
