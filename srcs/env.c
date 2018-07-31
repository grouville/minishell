/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 03:58:42 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:28:14 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_env(char ***c_env)
{
	int	i;

	i = -1;
	while (c_env[0][++i])
	{
		ft_putstr(c_env[0][i]);
		ft_putchar('\n');
	}
}

void		ft_print_error_env(char *av)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static int	ft_builtin_env3(char **av, char **cp_c_env, int i)
{
	int ret;

	ret = 0;
	if (ft_fork(av + i, av[i], &cp_c_env, 1))
		ft_print_error_env(av[i]);
	else
		ret = 1;
	return (ret);
}

static int	ft_builtin_env2(char **av, char **cp_c_env, int i, int ret)
{
	char	**path;
	int		j;

	j = 0;
	if (!ft_strchr(av[i], '/'))
	{
		path = ft_find_path_and_split(cp_c_env, av + i);
		while (path[++j])
			if (ft_fork(av + i, path[j], &cp_c_env, 0))
			{
				ret = 1;
				break ;
			}
		if (!path[j])
			ft_print_error_env(av[i]);
		ft_free_av(path);
	}
	else
	{
		if (ft_builtin_env3(av, cp_c_env, i))
			ret = 1;
	}
	return (ret);
}

int			ft_builtin_env(char **av, char ***c_env, int ret, int i)
{
	int		argc;
	char	**cp_c_env;

	argc = ft_len_array_char(av);
	ft_cp_env(&cp_c_env, *c_env);
	if (argc == 1)
		ft_print_env(c_env);
	else
		while (av[++i] && ret == 0)
		{
			if (ft_strchr(av[i], '='))
			{
				ft_builtin_setenv_2(av[i], &cp_c_env, 0);
				if (!av[i + 1])
					ft_print_env(&cp_c_env);
			}
			else
			{
				if (ft_builtin_env2(av, cp_c_env, i, 0))
					ret = 1;
			}
		}
	ft_free_av(cp_c_env);
	return (1);
}
