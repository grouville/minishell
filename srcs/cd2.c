/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 04:21:35 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:22:50 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_error(char *av, char *str)
{
	ft_putstr_fd(av, 2);
	ft_putstr_fd(str, 2);
}

void		ft_print_error_without_char(char *av, char *str)
{
	ft_putstr_fd_without_char(av, 2, '"');
	ft_putstr_fd(str, 2);
}

/*
*** - Fonction : Gestion d'erreur du cd - et PWD & OLDPWD non set
*/

void		ft_change_directory_and_modify_pwds(char *av, char ***c_env)
{
	char	*tmp;
	char	buf[1024];

	if ((access(av, F_OK)) == -1)
		ft_print_error(av, ": No such file or directory.\n");
	else if ((access(av, X_OK)) == -1)
		ft_print_error(av, ": Permission denied.\n");
	else
	{
		getcwd(buf, sizeof(buf));
		tmp = ft_strjoin("OLDPWD=", buf);
		ft_builtin_setenv_2(tmp, c_env, 0);
		free(tmp);
		chdir(av);
		getcwd(buf, sizeof(buf));
		tmp = ft_strjoin("PWD=", buf);
		ft_builtin_setenv_2(tmp, c_env, 0);
		free(tmp);
	}
}
