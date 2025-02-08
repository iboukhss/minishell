/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:55:21 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/08 02:57:12 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_xpipe(int pipefd[2])
{
	int	ret;

	ret = pipe(pipefd);
	if (ret == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
