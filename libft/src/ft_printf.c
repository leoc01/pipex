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

static int	ft_putarg(char format, va_list list);

int	ft_printf(const char *str, ...)
{
	va_list	list;
	size_t	len;

	len = 0;
	va_start(list, str);
	while (*str)
	{
		if (*str != '%')
			len += ft_putchar(*str);
		else
			len += ft_putarg(*(++str), list);
		str++;
	}
	va_end(list);
	return (len);
}

static int	ft_putarg(char format, va_list list)
{
	size_t	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(list, int));
	else if (format == 's')
		len += ft_putstr(va_arg(list, char *));
	else if (format == 'p')
		len += ft_putaddr(va_arg(list, unsigned long int));
	else if (format == 'd' || format == 'i')
		len += ft_putint(va_arg(list, int));
	else if (format == 'u')
		len += ft_putuint(va_arg(list, unsigned int), "0123456789");
	else if (format == 'x')
		len += ft_putuint(va_arg(list, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		len += ft_putuint(va_arg(list, unsigned int), "0123456789ABCDEF");
	else if (format == '%')
		len += ft_putchar('%');
	return (len);
}
