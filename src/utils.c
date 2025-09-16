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
	int		stdout_o;

	init_pipe(pipe_fd, stream_out);
	command->pid = fork();
	if (command->pid == 0)
	{
		dup2(command->stream_in, 0);
		close(command->stream_in);
		command->av = ft_split(cmd_string, ' ');
		command->pathname = find_path(command->av[0], envp);
		if (!stream_out)
			stream_out = pipe_fd[1];
		stdout_o = dup(1);
		dup2(stream_out, 1);
		close_pipe(pipe_fd, 2);
		if (command->stream_in >= 0)
			execve(command->pathname, command->av, envp);
		throw_error(command, stdout_o);
	}
	close(command->stream_in);
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
			break ;
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

void	throw_error(t_proc *command, int stdout_o)
{
	(void)stdout_o;
	ft_fprintf(2, "pipex: %s: command not found\n", command->av[0]);
	exit(127);
}
