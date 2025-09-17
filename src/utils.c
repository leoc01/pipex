/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:31:03 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/09/03 12:31:58 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	init_command(t_proc *command, char *cmd_string, char **envp);
static void	def_pathname(t_proc *command, char **possible_paths);
static char	*join_path(char *cmd, char *path);

int	run_cmd(char *cmd_string, char **envp, int stream_out, t_proc *command)
{
	int		pipe_fd[2];

	init_pipe(pipe_fd, stream_out);
	command->pid = fork();
	if (command->pid == 0)
	{
		dup2(command->stream_in, 0);
		close(command->stream_in);
		init_command(command, cmd_string, envp);
		if (!stream_out)
			stream_out = pipe_fd[1];
		dup2(stream_out, 1);
		close_pipe(pipe_fd, 2);
		if (command->stream_in < 0)
			throw_error(command);
		execve(command->pathname, command->av, envp);
		throw_error(command);
	}
	close(command->stream_in);
	close_pipe(pipe_fd, 1);
	return (pipe_fd[0]);
}

static void	init_command(t_proc *command, char *cmd_string, char **envp)
{
	int		i;
	char	**possible_paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return ;
	possible_paths = ft_split(&envp[i][5], ':');
	command->av = ft_split(cmd_string, ' ');
	def_pathname(command, possible_paths);
//	if (access(command->pathname, F_OK | X_OK) == -1)
//		command->cmd_error = errno;
}

static void	def_pathname(t_proc *command, char **possible_paths)
{
	char	*pathname;
	char	*temp_pathname;
	int		i;

	temp_pathname = NULL;
	i = 0;
	command->cmd_error = E_KO;
	while (possible_paths[i])
	{
		pathname = join_path(command->av[0], possible_paths[i]);
		if (access(pathname, F_OK | X_OK) == 0)
		{
			command->cmd_error = OK;
			if (temp_pathname)
				free(temp_pathname);
			temp_pathname = pathname;
			break;
		}
		else if (!temp_pathname && access(pathname, F_OK) == 0)
		{
			command->cmd_error = P_KO;
			temp_pathname = pathname;
		}
		free(command->pathname);
		i++;
	}
	command->pathname = temp_pathname;
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

void	init_pipe(int *pipe_fd, int stream_in)
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (!stream_in)
		pipe(pipe_fd);
}

void	close_pipe(int pipe_fd[2], int option)
{
	if (option != 1 && pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (option != 0 && pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

void	throw_error(t_proc *command)
{
	if (command->stream_in < 0)
		ft_fprintf(2, "pipex: %s: %s\n", command->filename, strerror(command->file_error));
	else if (command->cmd_error == P_KO)
	{
		ft_fprintf(2, "pipex: %s: permission denied\n", command->av[0]);
		exit(126);
	}
	else if (command->cmd_error == E_KO)
	{
		ft_fprintf(2, "pipex: %s: command not found\n", command->av[0]);
		exit(127);
	}
//	if (command->stream_in == FO_KO)
//		ft_fprintf(2, "pipex: %s: No such file or directory\n", command->filename);
	exit(1);
}
