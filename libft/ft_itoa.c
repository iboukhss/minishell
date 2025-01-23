/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:54:22 by dheck             #+#    #+#             */
/*   Updated: 2024/03/05 15:05:41 by dheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_create_str(int n, char *str_nbr, int nbr_len);
static int	ft_len_nbr(int n);

char	*ft_itoa(int n)
{
	char	*str_nbr;
	int		nbr_len;

	nbr_len = ft_len_nbr(n);
	str_nbr = malloc(sizeof(char) * (nbr_len + 1));
	if (str_nbr == 0)
		return (str_nbr);
	ft_create_str(n, str_nbr, nbr_len);
	return (str_nbr);
}

static void	ft_create_str(int n, char *str_nbr, int nbr_len)
{
	int	i;
	int	remainder;

	i = 0;
	remainder = 0;
	if (n < 0)
		str_nbr[i] = '-';
	if (n == 0)
		str_nbr[i] = '0';
	str_nbr[nbr_len] = '\0';
	nbr_len--;
	while (n != 0)
	{
		remainder = n % 10;
		if (remainder < 0)
			str_nbr[nbr_len] = (remainder * -1) + 48;
		else
			str_nbr[nbr_len] = remainder + 48;
		n = n / 10;
		nbr_len--;
	}
}

static int	ft_len_nbr(int n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len = 1;
		return (len);
	}
	if (n < 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
