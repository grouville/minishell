/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 04:00:43 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/22 06:06:32 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_av(char **av)
{
	int	i;

	i = -1;
	if (av)
		while (av[++i])
			free(av[i]);
	free(av);
}

int		ft_len_array_char(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

void	ft_exchange_chars(char **av, char delimitor, char to_replace)
{
	int		i;
	int		j;
	char	delimitor2;
	char	to_replace2;

	i = -1;
	delimitor2 = (delimitor == ' ' ? '\t' : (char)254);
	to_replace2 = (delimitor == ' ' ? (char)254 : '\t');
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == delimitor)
				av[i][j] = to_replace;
			else if (av[i][j] == delimitor2)
				av[i][j] = to_replace2;
		}
	}
}

int		ft_str_is_alpha(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '_')
			if (!ft_isalnum(str[i]))
				return (0);
	}
	return (1);
}

void	ft_swap_string(char **ret, char **tmp, char **c_env)
{
	*tmp = *ret;
	*ret = ft_strjoin(*tmp, *c_env);
	free(*tmp);
	*tmp = *ret;
	*ret = ft_strjoin(*tmp, " ");
	free(*tmp);
}
