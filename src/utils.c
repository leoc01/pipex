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
	char	*pathname;
	char	**cmd;
	int		pipe_fd[2];
	int		stdout_o;

	init_pipe(pipe_fd, stream_out);
	command->pid = fork();
	if (command->pid == 0)
	{
		dup2(command->stream_in, 0);
		close(command->stream_in);
		cmd = ft_split(cmd_string, ' ');
		pathname = find_path(cmd[0], envp);
		if (!stream_out)
			stream_out = pipe_fd[1];
		stdout_o = dup(1);
		dup2(stream_out, 1);
		close_pipe(pipe_fd, 2);
		if (command->stream_in >= 0)
			execve(pathname, cmd, envp);
		throw_error(cmd[0], stdout_o);
	}
	if (stream_out)
		close(stream_out);
	close_pipe(pipe_fd, 1);
	return (pipe_fd[0]);
}

char	*find_path(char *cmd, char **envp)
{
	char	**path;
	char	*right_path;
	char	*pathname;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = ft_split(&envp[i][5], ':');
	i = -1;
	while (path[++i])
	{
		right_path = ft_strjoin(path[i], "/");
		pathname = ft_strjoin(right_path, cmd);
		free(right_path);
		if (access(pathname, X_OK) == 0)
			break;
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

void	throw_error(char *cmd, int stdout_o)
{
	dup2(stdout_o, 1);
	ft_printf("%d\n", errno);
	ft_printf("pipex: %s: command not found\n", cmd);
	exit(127);
}
