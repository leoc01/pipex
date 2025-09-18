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
static int	def_exit(t_proc *command, int cmd_count, int outfile);

int	main(int argc, char **argv, char **envp)
{
	int		cmd_count;
	int		outfile;
	int		i;
	int		h;
//	int		exit_code;
	t_proc	*command;

	h = 0;
	if ((argc < 5) || (ft_strncmp(argv[1], "heredoc\0", 8) == 0 && argc < 6))
		return (1);
	cmd_count = argc - 3;
	if (ft_strncmp(argv[1], "heredoc\0", 8) == 0)
		h = 1;//cmd_count--;
	command = ft_calloc(cmd_count - h, sizeof(t_proc));
	if (!command)
		return (1);
	command[0].stream_in = open_infile(argv, &command[0]);
	i = 0;
	while (i + 1 < cmd_count - h)
	{
		command[i + 1].stream_in = run_cmd(argv[2 + i + h], envp, 0, command);
		i++;
	}
	outfile = open(argv[argc - 1], O_CREAT | O_WRONLY, 0664);
	if (outfile != -1)
		run_cmd(argv[2 + i + h], envp, outfile, command);
//	exit_code = def_exit(command, cmd_count, outfile);
	return (def_exit(command, cmd_count, outfile));
}

static int	def_exit(t_proc *command, int cmd_count, int outfile)
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
	if (ft_strncmp(file, "heredoc\0", 8) == 0)
		return (heredoc(argv[2]));
	command->f_name = file;
	if (access(file, F_OK) == -1)
		command->f_err = errno;
	else if (access(file, R_OK) == -1)
		command->f_err = errno;
	fd = open(file, O_RDONLY);
	return (fd);
}
