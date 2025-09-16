/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:25:23 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/05/06 13:47:40 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fputarg(int fd, char format, va_list list);

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	list;
	size_t	ln;

	ln = 0;
	va_start(list, str);
	while (*str)
	{
		if (*str != '%')
			ln += ft_putchar_fd(*str, fd);
		else
			ln += ft_fputarg(fd, *(++str), list);
		str++;
	}
	va_end(list);
	return (ln);
}

static int	ft_fputarg(int fd, char format, va_list lst)
{
	size_t	ln;

	ln = 0;
	if (format == 'c')
		ln += ft_putchar_fd(va_arg(lst, int), fd);
	else if (format == 's')
		ln += ft_putstr_fd(va_arg(lst, char *), fd);
	else if (format == 'p')
		ln += ft_putaddr_fd(va_arg(lst, unsigned long int), fd);
	else if (format == 'd' || format == 'i')
		ln += ft_putint_fd(va_arg(lst, int), fd);
	else if (format == 'u')
		ln += ft_putuint_fd(va_arg(lst, unsigned int), "0123456789", fd);
	else if (format == 'x')
		ln += ft_putuint_fd(va_arg(lst, unsigned int), "0123456789abcdef", fd);
	else if (format == 'X')
		ln += ft_putuint_fd(va_arg(lst, unsigned int), "0123456789ABCDEF", fd);
	else if (format == '%')
		ln += ft_putchar_fd('%', fd);
	return (ln);
}
