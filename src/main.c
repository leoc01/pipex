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
	int		stream_out;
	int		outfile;
	int		status;
	int		status_code;

	if (argc != 5)
		return (0);
	cmd_count = argc - 3;
	stream_out = open(argv[1], O_RDONLY);
	while (cmd_count > 1)
		stream_out = run_cmd(argv[argc - 1 - cmd_count--], envp, 0, stream_out);
	outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	(void)run_cmd(argv[argc - 1 - cmd_count], envp, outfile, stream_out);
	close(outfile);
	while (wait(&status) >= 0)
		status_code = WEXITSTATUS(status);
	return (status_code);
}
