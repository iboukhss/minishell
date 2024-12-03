/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 02:53:52 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/03 02:56:30 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xstrdup(const char *s)
{
	int		len;
	char	*dup;

	len = ft_strlen(s);
	dup = ft_xmalloc((len + 1) * sizeof(*dup));
	return (ft_memcpy(dup, s, len + 1));
}
