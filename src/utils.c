/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:31:03 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/09/17 15:43:39 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

void	throw_error(t_proc *cmd, int i)
{
	int	exit_code;

	wait(NULL);
	exit_code = 1;
	if (cmd[i].stream_in < 0)
	{
		ft_fprintf(2, "pipex: %s: %s\n", cmd[i].f_name, strerror(cmd[i].f_err));
	}
	else if (cmd[i].cmd_error == P_KO)
	{
		ft_fprintf(2, "pipex: %s: Permission denied\n", cmd[i].av[0]);
		exit_code = 126;
	}
	else if (cmd[i].cmd_error == E_KO)
	{
		ft_fprintf(2, "pipex: %s: Command not found\n", cmd[i].av[0]);
		exit_code = 127;
	}
	free(cmd[i].pathname);
	free_split(cmd[i].av);
	free(cmd);
	exit(exit_code);
}

void	free_split(char **str_array)
{
	int	i;

	if (str_array)
	{
		i = 0;
		while (str_array[i])
		{
			free(str_array[i]);
			i++;
		}
		free(str_array[i]);
		free(str_array);
	}
}
