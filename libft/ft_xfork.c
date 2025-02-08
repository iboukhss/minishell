/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:35:42 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/08 02:37:43 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t	ft_xfork(void)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
