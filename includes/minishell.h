/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gurival- <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/22 03:41:50 by gurival-     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:32:41 by gurival-    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <signal.h>

# define BLACKB    "\033[1;30m"
# define REDB      "\033[1;31m"
# define GREENB    "\033[1;32m"
# define YELLOWB   "\033[1;33m"
# define BLUEB     "\033[1;34m"
# define PURPLEB   "\033[1;35m"
# define CYANB     "\033[1;36m"
# define GREYB     "\033[1;37m"

# define BLACK    "\033[0;30m"
# define RED      "\033[0;31m"
# define GREEN    "\033[0;32m"
# define YELLOW   "\033[0;33m"
# define BLUE     "\033[0;34m"
# define PURPLE   "\033[0;35m"
# define CYAN     "\033[0;36m"
# define GREY     "\033[0;37m"

# define STOP     "\033[0;m"

int		g_glob;

/*
*** - Feuille : utils.c
*/
void	ft_free_av(char **av);
int		ft_len_array_char(char **av);
void	ft_exchange_chars(char **av, char delimitor, char to_replace);
int		ft_str_is_alpha(char *str);
void	ft_swap_string(char **ret, char **tmp, char **c_env);

/*
*** - Feuille : utils2.c
*/
char	*ft_array_char_to_str(char **c_env, int avoid);
int		ft_manage_var_env(char *av, char ***c_env,
			void (*f)(char *, char ***));
char	*ft_strdup_without_char(char *str, char c);
char	*ft_strdup_without_quotes(char *av, int len, int boolean);
void	ft_cp_env(char ***c_env, char **env);

/*
*** - Feuille : utils3.c
*/
void	ft_replace_back_spaces(char **av, char delimitor,
			char to_replace);
void	ft_putstr_fd_without_char(char *str, int fd, char c);
char	**ft_build_exec_path(char **path, char **av);
char	**ft_find_path_and_split(char **c_env, char **av);
void	ft_print_prompt(void);

/*
*** - Feuille : cd2.c
*/
void	ft_change_directory_and_modify_pwds(char *av, char ***c_env);
void	ft_print_error(char *av, char *str);
void	ft_print_error_without_char(char *av, char *str);

/*
*** - Feuille : cd.c
*/
char	*ft_replace_char_begin_string_to_string(char *str, char *av);
void	ft_find_path_and_cd(char c, char **av, char ***c_env);
int		ft_builtin_cd(char **av, char ***c_env);

/*
*** - Feuille : echo.c
*/
int		ft_manage_tild(char ***c_env);
int		ft_builtin_echo(char **av, char ***c_env);

/*
*** - Feuille : env. -- DES CHOSES A MODIFIER pour ne pas aller trop loin dans
*** - la boucle av[++i]
*/
int		ft_builtin_env(char **av, char ***c_env, int ret, int i);
void	ft_print_error_env(char *av);
void	ft_print_env(char ***c_env);

/*
*** - Feuille : main.c
*/
int		ft_built_in(char **av, char ***c_env);
int		ft_fork(char **av, char *path, char ***c_env, int bolean);
void	ft_execute(char **av, char ***c_env, int i);
int		main(int ret, char **av, char **env);

/*
*** - Feuille : setenv.c
*/
int		ft_str_is_alpha_setenv(char *str);
char	*ft_array_char_to_str_replace_env(char **c_env, int avoid, char *av);
void	ft_builtin_setenv_2(char *av, char ***c_env, int i);
int		ft_builtin_setenv(char **av, char ***c_env);

/*
*** - Feuille : unsetenv.c
*/
void	ft_builtin_unsetenv_2(char *av, char ***c_env);
int		ft_builtin_unsetenv(char **av, char ***c_env);
void	ft_replace_strdup_without_quote(char ***av, int boolean);

/*
*** - Feuille : var_\$.c
*/
int		ft_manage_var_env_illegal_name(char ***av);
char	*ft_replace_text_by_var(char *tmp2, char *av, char ***c_env);
int		ft_position_end_var(char *av, char c);
int		ft_replace_av_var_env(char ***av, char ***c_env);

/*
*** - Feuille : var_\$2.c
*/
char	*ft_strdup_change_var(char *av, char ***c_env, int i);

#endif
