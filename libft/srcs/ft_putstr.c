/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 18:16:43 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 18:06:18 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

void	ft_putstrfield(const char *str, int field, char justify)
{
	int		i;
	char	*o;

	if (field <= 0 || !str || !justify)
		return ;
	i = ft_strlen(str);
	o = ft_strnew(field - i);
	ft_memset(o, ' ', field - i);
	if (justify == 'r')
		ft_putstr(o);
	ft_putstr(str);
	if (justify == 'l')
		ft_putstr(o);
	free(o);
}
