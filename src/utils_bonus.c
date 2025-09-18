/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:32:12 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/09/18 15:42:48 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex_bonus.h>

int	heredoc(char *limiter)
{
	char	*line;
	char	*n_limiter;
	int		lim_len;
	int		heredoc;

	heredoc = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (heredoc != -1)
		unlink("heredoc");
	n_limiter = ft_strjoin(limiter, "\n");
	lim_len = ft_strlen(n_limiter);
	ft_printf("pipe heredoc>");
	line = get_next_line(1);
	while (line && strncmp(n_limiter, line, lim_len))
	{
		write(heredoc, line, ft_strlen(line));
		ft_printf("pipe heredoc>");
		line = get_next_line(1);
	}
	return (heredoc);
}
