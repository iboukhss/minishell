/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xrealloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:01:28 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 17:04:56 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

void	*ft_xrealloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (old_ptr == NULL)
	{
		return (ft_xmalloc(new_size));
	}
	else if (new_size == 0)
	{
		free(old_ptr);
		return (NULL);
	}
	else if (new_size <= old_size)
	{
		return (old_ptr);
	}
	new_ptr = ft_xmalloc(new_size);
	ft_memcpy(new_ptr, old_ptr, old_size);
	free(old_ptr);
	return (new_ptr);
}
