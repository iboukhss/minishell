/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:34:11 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/03 16:46:00 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"

#include "libft.h"
#include <string.h>

static int	write_char(t_file *f, va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	return (f->write(f, &c, 1));
}

static int	write_string(t_file *f, va_list ap)
{
	const char	*s;
	int			len;

	s = va_arg(ap, const char *);
	if (s == NULL)
	{
		s = "(null)";
	}
	len = ft_strlen(s);
	return (f->write(f, s, len));
}

static int	handle_specifier(t_file *f, char spec, va_list ap)
{
	if (spec == '%')
	{
		return (f->write(f, "%", 1));
	}
	else if (spec == 'c')
	{
		return (write_char(f, ap));
	}
	else if (spec == 's')
	{
		return (write_string(f, ap));
	}
	else
	{
		return (-1);
	}
}

int	printf_core(t_file *f, const char *fmt, va_list ap)
{
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			if (handle_specifier(f, *fmt, ap) == -1)
			{
				return (-1);
			}
		}
		else
		{
			if (f->write(f, fmt, 1) == -1)
			{
				return (-1);
			}
		}
		fmt++;
	}
	if (f->flush(f) == -1)
	{
		return (-1);
	}
	return (f->count);
}
