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

void	init_command(t_proc *command, char *cmd_string, char **envp)
{
	command->av = ft_split(cmd_string, ' ');
	command->pathname = find_path(command->av[0], envp);
	if (access(command->pathname, F_OK) == -1)
		command->cmd_error = errno;
	else if (access(command->pathname, X_OK) == -1)
		command->cmd_error = errno;
}

char	*get_pathname(char *cmd, char **path)
{
	char	*right_path;
	char	*pathname;
	int		i;
	
	i = -1;
	while (path[++i])
	{
		right_path = ft_strjoin(path[i], "/");
		pathname = ft_strjoin(right_path, cmd);
		free(right_path);
		if (access(pathname, X_OK) == 0)
			break ;
		free(pathname);
	}
	return (pathname);
}

char	*find_path(char *cmd, char **envp)
{
	char	**path;
	char	*pathname;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(&envp[i][5], ':');
	pathname = get_pathname(cmd, path[0]);
	i = 1;
	while (path[i] && access(pathname, X_OK) == -1)
	{
		free(pathname);
		pathname = get_pathname(cmd, path[i++]);
	}
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
	else
	{
		ft_fprintf(2, "pipex: %s: %s\n", command->av[0], strerror(command->cmd_error));
	}
//	if (command->stream_in == FO_KO)
//		ft_fprintf(2, "pipex: %s: No such file or directory\n", command->filename);
	exit(1);
}
