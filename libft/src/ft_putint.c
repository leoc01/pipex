/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuscaro <lbuscaro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:45:58 by lbuscaro          #+#    #+#             */
/*   Updated: 2025/04/29 13:46:11 by lbuscaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putint(int n)
{
	int	i;

	i = 0;
	if (n >= 0)
	{
		if (n >= 10)
		{
			i += ft_putint(n / 10);
		}
		i += ft_putchar(n % 10 + '0');
	}
	else if (n == INT_MIN)
	{
		ft_putstr("-2147483648");
		i = 11;
	}
	else
	{
		i += ft_putchar('-');
		i += ft_putint(n * -1);
	}
	return (i);
}
