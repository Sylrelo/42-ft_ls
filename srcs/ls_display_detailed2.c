/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_display_detailed2.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/21 13:49:10 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 18:28:19 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ls_print_symbolic_origin(t_ls *bt)
{
	char buff[255];

	if (bt->dtype == 10)
	{
		ft_memset(buff, '\0', 255);
		ft_putstr(" -> ");
		readlink(bt->name, buff, sizeof(buff));
		ft_putstr(buff);
	}
}

void	ls_print_size(struct stat *filestat, int col)
{
	ft_printspace(col - ft_intlen(filestat->st_size));
	ft_putnbr(filestat->st_size);
	write(1, " ", 1);
}

void	ls_print_size_hcol(long size, double q, char c)
{
	int len;

	len = ft_intlen((double)size * q);
	if (len >= 2 || c == 'B')
	{
		ft_printspace(3 - len);
		ft_putfloat((float)size * q, 0);
	}
	else
		ft_putfloat((float)size * q, 1);
	write(1, &c, 1);
}

void	ls_print_size_human(struct stat *filestat)
{
	long size;

	size = filestat->st_size;
	if (size >= 1000000000000)
		ls_print_size_hcol(size, 0.000000000001, 'T');
	else if (size >= 1000000000)
		ls_print_size_hcol(size, 0.000000001, 'G');
	else if (size >= 1000000)
		ls_print_size_hcol(size, 0.000000999760058, 'M');
	else if (size >= 1000)
		ls_print_size_hcol(size, 0.0009765625, 'K');
	else if (size < 1000)
		ls_print_size_hcol(size, 1, 'B');
	write(1, " ", 1);
}

void	ls_print_minormajor(t_ls *bt, t_lcols cols)
{
	int		min;
	int		maj;

	min = minor(bt->filestat->st_rdev);
	maj = major(bt->filestat->st_rdev);
	write(1, " ", 1);
	ft_printspace(cols.major - ft_intlen(maj));
	ft_putnbr(maj);
	write(1, ", ", 2);
	ft_printspace(cols.minor - ft_intlen(min));
	ft_putnbr(min);
	write(1, " ", 1);
}
