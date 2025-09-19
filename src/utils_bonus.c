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
	int		heredoc_f;

	heredoc_f = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0600);
	n_limiter = ft_strjoin(limiter, "\n");
	lim_len = ft_strlen(n_limiter);
	ft_printf("pipe heredoc>");
	line = get_next_line(0);
	while (line && strncmp(n_limiter, line, lim_len))
	{
		write(heredoc_f, line, ft_strlen(line));
		free(line);
		ft_printf("pipe heredoc>");
		line = get_next_line(0);
	}
	free(line);
	free(n_limiter);
	close(heredoc_f);
	heredoc_f = open("heredoc", O_RDONLY);
	unlink("heredoc");
	return (heredoc_f);
}
