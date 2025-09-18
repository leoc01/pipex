/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:31:03 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/09/17 19:16:35 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	init_command(t_proc *command, char *cmd_string, char **envp);
static void	def_pathname(t_proc *command, char **possible_paths);
static char	*join_path(char *cmd, char *path);

int	run_cmd(char *cmd_string, char **envp, int stream_out, t_proc *command)
{
	int			pipe_fd[2];
	static int	i;

	init_pipe(pipe_fd, stream_out);
	command[i].pid = fork();
	if (command[i].pid == 0)
	{
		dup2(command[i].stream_in, 0);
		close(command[i].stream_in);
		init_command(&command[i], cmd_string, envp);
		if (!stream_out)
			stream_out = pipe_fd[1];
		dup2(stream_out, 1);
		close_pipe(pipe_fd, 2);
		if (command[i].stream_in < 0 || command[i].cmd_error != 0)
			throw_error(command, i);
		execve(command[i].pathname, command[i].av, envp);
		throw_error(command, i);
	}
	close(command[i].stream_in);
	close_pipe(pipe_fd, 1);
	i++;
	return (pipe_fd[0]);
}

static void	init_command(t_proc *command, char *cmd_string, char **envp)
{
	int		i;
	char	**possible_paths;

	i = 0;
	command->av = ft_split(cmd_string, ' ');
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		command->cmd_error = E_KO;
		return ;
	}
	possible_paths = ft_split(&envp[i][5], ':');
	def_pathname(command, possible_paths);
	free_split(possible_paths);
}

static void	def_pathname(t_proc *command, char **possible_paths)
{
	char	*pathname;
	int		i;

	i = 0;
	command->cmd_error = E_KO;
	while (possible_paths[i])
	{
		pathname = join_path(command->av[0], possible_paths[i]);
		if (access(pathname, F_OK | X_OK) == 0)
		{
			command->cmd_error = OK;
			if (command->pathname)
				free(command->pathname);
			command->pathname = pathname;
			break ;
		}
		else if (!command->pathname && access(pathname, F_OK) == 0)
		{
			command->cmd_error = P_KO;
			command->pathname = pathname;
		}
		else
			free(pathname);
		i++;
	}
}

static char	*join_path(char *cmd, char *path)
{
	char	*right_path;
	char	*pathname;

	right_path = ft_strjoin(path, "/");
	pathname = ft_strjoin(right_path, cmd);
	free(right_path);
	return (pathname);
}
