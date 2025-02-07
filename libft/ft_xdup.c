/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:44:40 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/07 17:47:35 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_xdup(int fd)
{
	int	ret;

	ret = dup(fd);
	if (ret == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
