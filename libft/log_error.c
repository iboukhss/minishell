/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:55:57 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 12:08:59 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>

/*
 * Discarding the return value from ft_dprintf.
 */
void	log_error(const char *s)
{
	ft_dprintf(STDERR_FILENO, "%s\n", s);
}
