/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_$.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 04:10:01 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 19:13:35 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int		ft_manage_var_env_illegal_name(char ***av)
{
	int		i;
	char	*ret;

	i = 0;
	while ((*av)[++i])
		if ((ret = ft_strchr((*av)[i], '$')) && (*(ret + 1) == '"'))
		{
			ft_putstr_fd("Illegal variable name.\n", 2);
			return (1);
		}
	return (0);
}

char	*ft_replace_text_by_var(char *tmp2, char *av, char ***c_env)
{
	int		count;
	char	*ret;

	count = 0;
	while ((*c_env)[count] && ft_strncmp((*c_env)[count],
				av + 1, ft_strlen(av) - 1))
		count++;
	if ((*c_env)[count])
	{
		ret = ft_strdup(ft_strchr((*c_env)[count], '=') + 1);
		free(av);
		av = ft_strjoin(tmp2, ret);
		free(ret);
		free(tmp2);
		return (av);
	}
	else
	{
		ft_putstr_fd(av + 1, 2);
		ft_putstr_fd(": Undefined variable.\n", 2);
		free(av);
		free(tmp2);
	}
	return (NULL);
}

int		ft_position_end_var(char *av, char c)
{
	int	i;

	i = 0;
	while (av[i] && (av[i] != ' ' && av[i] != '	' && av[i] != c
				&& av[i] != (char)255 && av[i] != '"'))
		i++;
	i++;
	return (i);
}

int		ft_replace_av_var_env(char ***av, char ***c_env)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = -1;
	if (!**av)
		return (1);
	if (ft_manage_var_env_illegal_name(av))
		return (1);
	ft_replace_strdup_without_quote(av, 0);
	while ((*av)[++i])
	{
		if ((ret = ft_strchr((*av)[i], '$'))
				&& (ft_isalnum(*(ret + 1)) || (*(ret + 1) == '_')))
		{
			if (!(tmp = ft_strdup_change_var((*av)[i], c_env, 0)))
				return (1);
			free((*av)[i]);
			(*av)[i] = ft_strdup(tmp);
			free(tmp);
		}
	}
	return (0);
}
