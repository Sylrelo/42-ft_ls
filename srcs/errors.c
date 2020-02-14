/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   errors.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 18:49:56 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 16:18:46 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	error_invalid_options(char *c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putendl(c);
	ft_putendl("usage: ft_ls [-larRt1GhHinTSuU] [file ...]");
	exit(1);
}

void	p_error(char c)
{
	if (c == 'm')
		ft_putendl("Memory allocation failed. Re-run the program\
					to try again.");
	exit(1);
}
