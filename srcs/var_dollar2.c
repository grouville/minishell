/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   var_$.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 04:10:01 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:56:59 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

static char		*ft_n2(char *res, char *tmp, char *tmp2, char *av)
{
	tmp2 = res;
	tmp = ft_strdup(av);
	res = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (res);
}

static char		*ft_norme_1(char *res, char *tmp, char *tmp2)
{
	tmp2 = res;
	res = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (res);
}

char			*ft_strdup_change_var(char *av, char ***c_env, int i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	char	*res;
	int		len_end;

	res = NULL;
	ft_replace_spaces_inside_quotes(av, ' ', (char)255);
	while (av[i] && (ret = ft_strchr(av + i, '$')))
	{
		if ((ret) && (tmp = ft_strsub(av, i, (ret - (av + i)))))
		{
			res = (res ? ft_norme_1(res, tmp, tmp2) : tmp);
			i = ret - av;
			len_end = ft_position_end_var(av + i + 1, '$');
			tmp2 = res;
			tmp = ft_strsub(av, i, len_end);
			if (!(res = ft_replace_text_by_var(tmp2, tmp, c_env)))
				return (NULL);
			i = i + len_end;
		}
		if (!ft_strchr(av + i, '$') && (res = ft_n2(res, tmp, tmp2, av + i)))
			break ;
	}
	return (res);
}
