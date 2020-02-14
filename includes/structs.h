/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   structs.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 18:44:13 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 20:17:33 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/syslimits.h>

typedef struct			s_params
{
	int					recur;
	int					r;
	int					t;
	int					a;
	int					h;
	int					l;
	int					color;
	int					symbolicfollow;
	int					inode;
	int					n;
	int					fulltime;
	int					sortsize;
	int					lastaccess;
	int					creationdate;

}						t_params;

typedef struct			s_dirlist
{
	char				*name;
	struct s_dirlist	*next;
}						t_dirlist;

typedef struct			s_ls
{
	char				name[PATH_MAX];
	char				dname[NAME_MAX];
	int					isolo;
	int					dtype;
	long int			timesec;
	struct dirent		*dent;
	struct stat			*filestat;
	struct s_ls			*next;
	struct s_ls			*right;

}						t_ls;

typedef struct			s_lcols
{
	int					size;
	int					pwduid;
	int					grpuid;
	int					major;
	int					minor;
	int					lnkcount;
	int					inode;
}						t_lcols;

typedef struct			s_env
{
	t_ls				*ls;
	t_dirlist			*dirs;
	t_params			p;
	t_lcols				cols;
	int					isfile;
	int					count;
}						t_env;

typedef struct			s_insert
{
	char				name[NAME_MAX];
	char				path[PATH_MAX];
	char				cdir[PATH_MAX];
	int					type;
	struct stat			*filestat;

}						t_insert;

typedef struct			s_checks
{
	char				path[PATH_MAX];
	struct s_checks		*next;
}						t_checks;

#endif
