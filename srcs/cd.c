/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 04:21:35 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:24:12 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_replace_char_begin_string_to_string(char *str, char *av)
{
	char	*tmp;

	tmp = ft_strjoin(str, av + 1);
	return (tmp);
}

static void	ft_find_path_and_cd2(char c)
{
	if (c == '~')
		ft_putstr_fd("No $home variable set.\n", 2);
	else
		ft_putstr_fd("No $OLDPWD variable set.\n", 2);
}

void		ft_find_path_and_cd(char c, char **av, char ***c_env)
{
	int		count;
	char	*tmp;
	char	*tmp2;

	count = 0;
	while ((*c_env)[count] && ft_strncmp((*c_env)[count],
				(c == '~' ? "HOME=" : "OLDPWD="), (c == '~' ? 5 : 7)))
		count++;
	if ((*c_env)[count])
	{
		tmp = ft_strdup(ft_strchr((*c_env)[count], '=') + 1);
		if (av[1] && av[1][0] == '~' && ft_strlen(av[1]) > 1)
		{
			tmp2 = ft_replace_char_begin_string_to_string(tmp, av[1]);
			ft_change_directory_and_modify_pwds(tmp2, c_env);
			free(tmp2);
		}
		else
			ft_change_directory_and_modify_pwds(tmp, c_env);
		free(tmp);
	}
	else
		ft_find_path_and_cd2(c);
}

int			ft_builtin_cd(char **av, char ***c_env)
{
	int		count;
	int		argc;

	count = 0;
	argc = ft_len_array_char(av);
	if (argc == 1 || (argc == 2 && av[1][0] == '~'))
		ft_find_path_and_cd('~', av, c_env);
	else if (argc == 2 && !ft_strcmp(av[1], "-"))
		ft_find_path_and_cd('-', av, c_env);
	else if (argc == 2)
		ft_change_directory_and_modify_pwds(av[1], c_env);
	else
		ft_putstr_fd("cd: Too many arguments.\n", 2);
	return (1);
}
