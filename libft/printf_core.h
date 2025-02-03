/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:34:04 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/02 20:59:58 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_CORE_H
# define PRINTF_CORE_H

# include <stdarg.h>

typedef struct s_file
{
	int		fd;
	char	*data;
	int		len;
	int		cap;
	int		count;
	int		(*write)(struct s_file *, const void *, int);
	int		(*flush)(struct s_file *);
}	t_file;

int	printf_core(t_file *f, const char *fmt, va_list ap);

#endif
