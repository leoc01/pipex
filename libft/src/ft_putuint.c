/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:45:58 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/04/29 13:46:11 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putuint(unsigned int n, char *base)
{
	size_t	div;
	size_t	i;

	i = 0;
	div = ft_strlen(base);
	if (n >= div)
	{
		i += ft_putuint(n / div, base);
	}
	i += ft_putchar(base[n % div]);
	return (i);
}
