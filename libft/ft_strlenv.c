/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:09:17 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/14 17:10:54 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlenv(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i] != NULL)
	{
		i++;
	}
	return (i);
}
