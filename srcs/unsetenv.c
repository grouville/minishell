/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   unsetenv.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 05:44:32 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 06:05:25 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_unsetenv_2(char *av, char ***c_env)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while ((*c_env)[i] && ft_strncmp((*c_env)[i], av, ft_strlen(av)))
		i++;
	if ((*c_env)[i])
	{
		ft_exchange_chars(*c_env, ' ', (char)255);
		ret = ft_array_char_to_str(*c_env, i);
		ft_free_av(c_env[0]);
		c_env[0] = ft_strsplit(ret, ' ');
		ft_exchange_chars(*c_env, (char)255, ' ');
		free(ret);
	}
}

int		ft_builtin_unsetenv(char **av, char ***c_env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_len_array_char(av);
	if (len == 1)
		ft_putstr_fd("unsetenv: Too few arguments\n", 2);
	while (len != 1 && av[++i])
		ft_builtin_unsetenv_2(av[i], c_env);
	return (1);
}

void	ft_replace_strdup_without_quote(char ***av, int boolean)
{
	int		i;
	char	*tmp;
	int		exception;

	i = -1;
	exception = ((!ft_strcmp((*av)[0], "\"setenv\"")
		|| !ft_strcmp((*av)[0], "\"exit\"")
			|| !ft_strcmp((*av)[0], "setenv")) ? 1 : 0);
	if (boolean == 0)
		exception = ((!ft_strcmp((*av)[0], "echo")) ? 1 : exception);
	while ((*av)[++i])
	{
		if (((exception == 1) ? (exception == 0) : 1))
		{
			tmp = ft_strdup_without_quotes((*av)[i], 0, 0);
			free((*av)[i]);
			(*av)[i] = ft_strdup(tmp);
			free(tmp);
		}
	}
}
