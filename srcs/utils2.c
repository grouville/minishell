/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 04:05:49 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 06:08:50 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_array_char_to_str(char **c_env, int avoid)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = -1;
	ret = NULL;
	tmp = NULL;
	while (c_env[++i])
		if (i != avoid)
			ft_swap_string(&ret, &tmp, &c_env[i]);
	return (ret);
}

int		ft_manage_var_env(char *av, char ***c_env, void (*f)(char *, char ***))
{
	int		count;

	count = 0;
	while ((*c_env)[count] && ft_strncmp((*c_env)[count], av + 1,
		ft_strlen(av) - 1))
		count++;
	if (!(*c_env)[count])
	{
		ft_putstr_fd(av + 1, 2);
		ft_putstr_fd(": Undefined variable.\n", 2);
		return (1);
	}
	else
		(*f)(ft_strchr((*c_env)[count], '=') + 1, c_env);
	return (0);
}

char	*ft_strdup_without_char(char *str, char c)
{
	char	*dest;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != c)
			j++;
	if ((dest = (char*)malloc(sizeof(char) * (j + 1))) == NULL)
		return (0);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != c)
		{
			dest[j] = str[i];
			j++;
		}
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strdup_without_quotes(char *av, int len, int boolean)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	if (ft_strlen(av) == (size_t)len)
		ret = ft_strdup(av);
	else
	{
		if (ft_strchr(av + len, '"'))
			ret = ft_strdup_without_char(av, '"');
		else
			ret = ft_strdup(av);
	}
	if (boolean == 1 && !ft_strchr(ret, '='))
	{
		tmp = ret;
		ret = ft_strjoin(tmp, "=");
		free(tmp);
	}
	return (ret);
}

void	ft_cp_env(char ***c_env, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	if (!(c_env[0] = (char **)malloc(sizeof(char *) * (i + 1))))
		return ;
	i = -1;
	while (env[++i])
		c_env[0][i] = ft_strdup(env[i]);
	c_env[0][i] = NULL;
}
