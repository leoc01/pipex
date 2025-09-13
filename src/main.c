/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:26:54 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/09/12 09:23:45 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv, char **envp)
{
	int		cmd_count;
	int		outfile;
	int		i;
	int		exit_code;
	t_proc	*child;

	if (argc != 5)
		return (0);
	cmd_count = argc - 3;
	child = ft_calloc(cmd_count, sizeof(t_proc));
	if (!child)
		return (1);
	child[0].stream_in = open(argv[1], O_RDONLY);
	i = -1;
	while (++i + 1 < cmd_count)
		child[i + 1].stream_in = run_cmd(argv[2 + i], envp, 0, &child[i]);
	outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	(void)run_cmd(argv[2 + i], envp, outfile, &child[i]);
	close(outfile);
	i = 0;
	while (++i < cmd_count)
		waitpid(child[i].pid, &child[i].status, 0);
	exit_code = WEXITSTATUS(child[i].status);
	free(child);
	return (exit_code);
}
