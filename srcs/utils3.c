/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils3.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 04:26:21 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:31:15 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

/*
*** - Function : for the echo command
*/

void	ft_replace_back_spaces(char **av, char delimitor, char to_replace)
{
	int		i;

	i = -1;
	while (av[++i])
		ft_replace_spaces_inside_quotes(av[i], delimitor, to_replace);
}

/*
*** - Function : PUTSTR_FOR THE "EXIT" AND "SETENV" MANAGEMENT
*/

void	ft_putstr_fd_without_char(char *str, int fd, char c)
{
	int	i;

	i = -1;
	if (str != NULL)
	{
		while (str[++i])
		{
			if (str[i] != c)
				ft_putchar_fd(str[i], fd);
		}
	}
}

char	**ft_build_exec_path(char **path, char **av)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	tmp = ft_strdup(av[0]);
	tmp2 = ft_strjoin("/", tmp);
	free(tmp);
	while (path[++i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(tmp, tmp2);
		free(tmp);
	}
	free(tmp2);
	return (path);
}

char	**ft_find_path_and_split(char **c_env, char **av)
{
	int		i;
	char	**ret;
	char	**res;

	i = 0;
	while (c_env[i] && ft_strncmp(c_env[i], "PATH=", 5))
		i++;
	if (c_env[i] && c_env[i][6])
	{
		ret = ft_strsplit(c_env[i], '=');
		res = ft_strsplit(ret[1], ':');
		ft_free_av(ret);
		res = ft_build_exec_path(res, av);
	}
	else
		res = ft_strsplit("cest=un=test", '=');
	return (res);
}

void	ft_print_prompt(void)
{
	ft_putstr_fd(PURPLE, 1);
	ft_putstr_fd("my_csh-3.2$ 🔥  ", 1);
	ft_putstr_fd(STOP, 1);
}
