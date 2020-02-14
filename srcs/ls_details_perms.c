/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_details_perms.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/17 17:30:01 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 18:04:33 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	perms_extended(t_ls *bt)
{
	acl_t	acl;

	if (listxattr(bt->name, NULL, 0, XATTR_NOFOLLOW) > 0)
		write(1, "@ ", 2);
	else if ((acl = acl_get_file(bt->name, ACL_TYPE_EXTENDED)) != NULL)
	{
		write(1, "+ ", 2);
		acl_free(acl);
	}
	else
		write(1, "  ", 2);
}

static void	perms_user(char *tperms, mode_t stmode)
{
	tperms[1] = (stmode & S_IRUSR) ? 'r' : '-';
	tperms[2] = (stmode & S_IWUSR) ? 'w' : '-';
	tperms[3] = (stmode & S_IXUSR) ? 'x' : '-';
	if ((stmode & S_ISUID))
		tperms[3] = (stmode & S_IXUSR) ? 's' : 'S';
	tperms[4] = (stmode & S_IRGRP) ? 'r' : '-';
	tperms[5] = (stmode & S_IWGRP) ? 'w' : '-';
	tperms[6] = (stmode & S_IXGRP) ? 'x' : '-';
	if ((stmode & S_ISGID))
		tperms[6] = (stmode & S_IXGRP) ? 's' : 'S';
	tperms[7] = (stmode & S_IROTH) ? 'r' : '-';
	tperms[8] = (stmode & S_IWOTH) ? 'w' : '-';
	tperms[9] = (stmode & S_IXOTH) ? 'x' : '-';
	if ((stmode & S_ISVTX))
		tperms[9] = (stmode & S_IXOTH) ? 't' : 'T';
}

void		ls_print_perms(t_ls *bt)
{
	char		tperms[11];
	mode_t		stmode;

	stmode = bt->filestat->st_mode;
	ft_memset(tperms, '-', 10);
	tperms[10] = '\0';
	if ((S_ISREG(stmode)))
		tperms[0] = '-';
	else if ((S_ISDIR(stmode)))
		tperms[0] = 'd';
	else if ((S_ISLNK(stmode)))
		tperms[0] = 'l';
	else if ((S_ISBLK(stmode)))
		tperms[0] = 'b';
	else if ((S_ISSOCK(stmode)))
		tperms[0] = 's';
	else if ((S_ISCHR(stmode)))
		tperms[0] = 'c';
	else if ((S_ISFIFO(stmode)))
		tperms[0] = 'p';
	else
		tperms[0] = ' ';
	perms_user(tperms, stmode);
	write(1, tperms, 10);
	perms_extended(bt);
}
