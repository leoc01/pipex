/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:26:54 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/09/15 11:02:58 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	open_infile(char *file, t_proc *command);

int	main(int argc, char **argv, char **envp)
{
	int		cmd_count;
	int		outfile;
	int		i;
	int		exit_code;
	t_proc	*command;

	if (argc != 5)
		return (1);
	cmd_count = argc - 3;
	command = ft_calloc(cmd_count, sizeof(t_proc));
	if (!command)
		return (1);
	command[0].stream_in = open_infile(argv[1], &command[0]);
	i = -1;
	while (++i + 1 < cmd_count)
		command[i + 1].stream_in = run_cmd(argv[2 + i], envp, 0, &command[i]);
	outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	(void)run_cmd(argv[2 + i], envp, outfile, &command[i]);
	i = -1;
	while (++i < cmd_count)
		waitpid(command[i].pid, &command[i].status, 0);
	exit_code = WEXITSTATUS(command[--i].status);
	close(outfile);
	free(command);
	return (exit_code);
}

static int	open_infile(char *file, t_proc *command)
{
	int	fd;

	command->filename = file;
	if (access(file, F_OK) == -1)
		command->file_error = errno;
	else if (access(file, R_OK) == -1)
		command->file_error = errno;
	fd = open(file, O_RDONLY);
	return (fd);
}
