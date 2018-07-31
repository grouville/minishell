/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 03:43:30 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 19:57:09 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "minishell.h"

int			ft_built_in(char **av, char ***c_env)
{
	ft_exchange_chars(av, (char)255, ' ');
	if (ft_strcmp(av[0], "unsetenv") == 0)
		return (ft_builtin_unsetenv(av, c_env));
	if (ft_strcmp(av[0], "setenv") == 0)
		return (ft_builtin_setenv(av, c_env));
	if (ft_strcmp(av[0], "echo") == 0)
		return (ft_builtin_echo(av, c_env));
	if (ft_strcmp(av[0], "env") == 0)
		return (ft_builtin_env(av, c_env, 0, 0));
	if (ft_strcmp(av[0], "cd") == 0)
		return (ft_builtin_cd(av, c_env));
	return (0);
}

int			ft_fork(char **av, char *path, char ***c_env, int bolean)
{
	pid_t		father;
	struct stat	buf;

	if ((g_glob = 1) && lstat(path, &buf) != -1)
	{
		father = fork();
		if (father == 0)
		{
			if (S_ISREG(buf.st_mode))
			{
				if (execve(path, av, *c_env) == -1)
					exit(1);
			}
			else
				exit(1);
		}
		if (father > 0)
			wait(NULL);
	}
	g_glob = 0;
	if (bolean == 0 && lstat(path, &buf) != -1)
		return (1);
	else if (bolean == 1 && lstat(path, &buf) != -1 && S_ISDIR(buf.st_mode))
		ft_print_error(av[0], ": Permission denied.\n");
	else if (bolean == 1 && lstat(path, &buf) == -1)
		ft_print_error_without_char(av[0], ": Command not found.\n");
	return (0);
}

void		ft_execute(char **av, char ***c_env, int i)
{
	char	**path;
	int		ret;

	ret = 0;
	if (ft_strcmp(av[0], "exit") == 0)
		exit(1);
	if (ft_built_in(av, c_env) != 0)
		return ;
	path = ft_find_path_and_split(*c_env, av);
	ft_exchange_chars(av, (char)255, ' ');
	if (!ft_strchr(av[0], '/') && ft_strcmp(av[0], ".."))
	{
		while (path[++i] && ft_strcmp(av[0], "."))
			if (ft_fork(av, path[i], c_env, 0) == 1)
				break ;
		if (!path[i] || !ft_strcmp(av[0], "."))
		{
			ft_putstr_fd_without_char(av[0], 2, '"');
			ft_putstr_fd(": Command not found.\n", 2);
		}
	}
	else
		ft_fork(av, av[0], c_env, 1);
	ft_free_av(path);
}

static void	sighandler(int signum)
{
	(void)signum;
	ft_putstr("\n");
	if (g_glob == 0)
		ft_print_prompt();
}

int			main(int ret, char **av, char **env)
{
	char	*line;
	char	**c_env;

	line = NULL;
	g_glob = 0;
	signal(SIGINT, sighandler);
	ft_cp_env(&c_env, env);
	while (42)
	{
		ft_print_prompt();
		ret = get_next_line(0, &line);
		if (ret == 0)
			exit(1);
		if (line && ft_strlen(line) > 0)
		{
			av = ft_strsplit_quote_new(line, ' ', (char)255);
			if (!ft_replace_av_var_env(&av, &c_env))
				ft_execute(av, &c_env, -1);
			ft_free_av(av);
		}
		free(line);
	}
	ft_free_av(c_env);
	return (0);
}
