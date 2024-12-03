/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdupv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 02:53:08 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/03 03:02:20 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_xstrdupv(char **str_array)
{
	int		count;
	int		i;
	char	**dup;

	count = 0;
	while (str_array[count] != NULL)
	{
		count++;
	}
	dup = ft_xmalloc((count + 1) * sizeof(*dup));
	i = 0;
	while (i < count)
	{
		dup[i] = ft_xstrdup(str_array[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
