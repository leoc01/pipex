/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:29:30 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/09/16 11:21:53 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# define FO_KO -1
# define FE_KO -2
# define FR_KO -3

typedef struct s_proc
{
	int		pid;
	int		stream_in;
	int		file_error;
	char	*filename;
	char	*pathname;
	char	**av;
	int		cmd_error;
	int		status;
}	t_proc;

int		run_cmd(char *cmd_string, char **envp, int stream_out, t_proc *child);
void	init_command(t_proc *command, char *cmd_string, char **envp);
char	*find_path(char *cmd, char **envp);

void	init_pipe(int *pipe_fd, int file);
void	close_pipe(int pipe_fd[2], int option);

void	throw_error(t_proc *command);

#endif
