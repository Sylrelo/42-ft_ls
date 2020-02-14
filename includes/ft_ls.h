/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 18:44:11 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 16:18:43 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/includes/libft.h"
# include "structs.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/ioctl.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# define VALID_OPTS "larRt1GhHinTSuU"

void		p_error(char c);

/*
**			PARSING OPTIONS
*/
void		opt_handle(t_env *env, char **argv);
void		error_invalid_options(char *c);
/*
**			FREE STUFF
*/
void		ls_free_readdirs(t_ls *head);
void		ls_free_readfiles(t_ls *bt);
void		ls_free_all(t_env *env);
void		ls_free_chk(t_checks *chk);
/*
**			READER
*/
int			ls_solofiles(t_env **env, t_checks **chk);
int			ls_readdir(char *cdir, t_env **env, t_ls *bt, t_checks *chk);
/*
**			LIST UTILS
*/
void		ls_list_insert(t_env *env, t_ls **head, \
								struct dirent *dent, char *cdir);
void		ls_list_fileinsert(t_env *env, struct stat *filestat, \
										char *fname);
int			ls_list_check(t_checks *head, char *path);
void		ls_list_insert_check(t_checks **head, char *path);
void		ls_list_insert_sort(t_env *env, t_ls **head, t_ls *newl);
void		ls_reverse(t_ls **head);
void		ls_sort_swap(t_ls **prev, t_ls **curr);
long int	ls_handletime(t_env *env, struct stat *stat);
/*
**			MISC
*/
void		ls_recursion(t_env **env, t_ls *ls);
int			ls_file_type(struct stat *filestat);
void		ls_display(t_env **env, t_ls *bt);
struct stat	*ls_get_filestat(t_ls *bt);
/*
**			DETAILED INFORMATION ABOUT FILE
*/
void		lcol_init(t_env **env, t_ls *bt);
void		ls_print_minormajor(t_ls *bt, t_lcols cols);
void		ls_print_size(struct stat *filestat, int col);
void		ls_print_size_human(struct stat *filestat);
void		ls_print_symbolic_origin(t_ls *bt);
void		ls_print_date(t_params p, long int timesec);
void		ls_print_uid(t_env **env, struct stat *filestat);
void		ls_print_perms(t_ls *bt);
void		ls_print_totalblock(t_ls *bt);
void		ls_print_countsub(t_ls *bt, int col);
void		ls_print_inode (t_ls *bt, int col);

#endif
