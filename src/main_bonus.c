/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:26:54 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/09/18 11:40:57 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

static int	open_infile(char **argv, t_proc *command);
static int	open_outfile(char *filename, int heredoc);
static int	run_exit(t_proc *command, int cmd_count, int outfile);

int	main(int argc, char **argv, char **envp)
{
	int		cmd_count;
	int		outfile;
	int		i;
	int		h;
	t_proc	*command;

	h = 0;
	if ((argc < 5) || (ft_strncmp(argv[1], "here_doc\0", 9) == 0 && argc < 6))
		return (1);
	if (ft_strncmp(argv[1], "here_doc\0", 9) == 0)
		h = 1;
	cmd_count = argc - 3 - h;
	command = ft_calloc(cmd_count, sizeof(t_proc));
	if (!command)
		return (1);
	command[0].stream_in = open_infile(argv, &command[0]);
	i = -1;
	while (++i + 1 < cmd_count)
	{
		command[i + 1].stream_in = run_cmd(argv[2 + i + h], envp, 0, command);
	}
	outfile = open_outfile(argv[argc - 1], h);
	if (outfile != -1)
		run_cmd(argv[2 + i + h], envp, outfile, command);
	return (run_exit(command, cmd_count, outfile));
}

static int	run_exit(t_proc *command, int cmd_count, int outfile)
{
	int	i;
	int	exit_code;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(command[i].pid, &command[i].status, 0);
		i++;
	}
	exit_code = WEXITSTATUS(command[cmd_count - 1].status);
	close(outfile);
	free(command);
	if (outfile == -1)
		exit_code = 1;
	return (exit_code);
}

static int	open_infile(char **argv, t_proc *command)
{
	int		fd;
	char	*file;

	file = argv[1];
	if (ft_strncmp(file, "here_doc\0", 9) == 0)
		return (heredoc(argv[2]));
	command->f_name = file;
	if (access(file, F_OK) == -1)
		command->f_err = errno;
	else if (access(file, R_OK) == -1)
		command->f_err = errno;
	fd = open(file, O_RDONLY);
	return (fd);
}

static int	open_outfile(char *filename, int heredoc)
{
	int	outfile;

	if (heredoc)
		outfile = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	return (outfile);
}
