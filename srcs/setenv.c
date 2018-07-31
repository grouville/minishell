/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   setenv.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 03:58:50 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:28:42 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int			ft_str_is_alpha_setenv(char *str)
{
	int		i;
	int		len;

	i = -1;
	len = (ft_strchr(str, '=') ? ft_strchr(str, '=') - str : ft_strlen(str));
	while (str[++i] && i < len)
	{
		if (str[i] != '_' && str[i] != '=')
			if (!ft_isalnum(str[i]))
				return (0);
	}
	return (1);
}

char		*ft_array_char_to_str_replace_env(char **c_env, int avoid, char *av)
{
	char	*ret;
	char	*tmp;
	char	*cp_av;
	int		i;

	i = -1;
	ret = NULL;
	tmp = NULL;
	cp_av = NULL;
	while (c_env[++i])
	{
		if (i != avoid)
			ft_swap_string(&ret, &tmp, &c_env[i]);
		else
		{
			if (!ft_strchr(av, '='))
				cp_av = ft_strjoin(av, "=");
			else
				cp_av = ft_strdup(av);
			ft_swap_string(&ret, &tmp, &cp_av);
			free(cp_av);
		}
	}
	return (ret);
}

static void	ft_builtin_setenv_3(char ***c_env, int i, char *tmp)
{
	char	*ret;
	char	*ret2;

	ret2 = ft_array_char_to_str_replace_env(*c_env, i, tmp);
	ret = ft_strjoin(ret2, tmp);
	free(ret2);
	free(tmp);
	ft_free_av(c_env[0]);
	c_env[0] = ft_strsplit(ret, ' ');
	ft_exchange_chars(*c_env, (char)255, ' ');
	free(ret);
}

void		ft_builtin_setenv_2(char *av, char ***c_env, int i)
{
	int		len;
	char	*ret;
	char	*tmp;

	len = (ft_strchr(av, '=') ? ft_strchr(av, '=') - av : ft_strlen(av));
	tmp = ft_strdup_without_quotes(av, len, 1);
	ft_exchange_chars(*c_env, ' ', (char)255);
	while ((*c_env)[i] && ft_strncmp((*c_env)[i], av, len))
		i++;
	if ((*c_env)[i])
	{
		ret = ft_array_char_to_str_replace_env(*c_env, i, tmp);
		free(tmp);
		ft_free_av(c_env[0]);
		*c_env = ft_strsplit(ret, ' ');
		ft_exchange_chars(c_env[0], (char)255, ' ');
		free(ret);
	}
	else
		ft_builtin_setenv_3(c_env, i, tmp);
}

int			ft_builtin_setenv(char **av, char ***c_env)
{
	int		len;

	len = ft_len_array_char(av);
	if (len == 1)
		ft_print_env(c_env);
	if (len > 2)
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	ft_exchange_chars(av, ' ', (char)255);
	if (len == 2)
	{
		if (av[1][0] == '"' || av[1][0] == '~' || !ft_isalpha(av[1][0]))
			ft_putstr_fd("setenv: Variable name must begin with a letter.\n",
					2);
		else if (!ft_str_is_alpha_setenv(av[1]))
			ft_print_error("setenv: Variable name must",
				" contain alphanumeric characters.\n");
		else
			ft_builtin_setenv_2(av[1], c_env, 0);
	}
	return (1);
}
