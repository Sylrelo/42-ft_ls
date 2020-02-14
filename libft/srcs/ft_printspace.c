/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printspace.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/27 15:19:31 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/28 10:38:24 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_printspace(int nb)
{
	int		i;
	char	*str;

	if (nb <= 0)
		return ;
	if (!(str = malloc(sizeof(char) * nb)))
		return ;
	i = -1;
	while (++i < nb)
		str[i] = ' ';
	write(1, str, nb);
	free(str);
}
