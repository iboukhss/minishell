/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:40:51 by dheck             #+#    #+#             */
/*   Updated: 2024/12/14 17:13:21 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

// Standard libc functions
char	*ft_strchr(const char *s, int c);
char	*ft_strchrnul(const char *s, int c);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);

// Fail-safe alloc functions
void	*ft_xmalloc(size_t size);
char	*ft_xstrdup(const char *s);

// String array functions (glib)
char	**ft_xstrdupv(char **str_array);
void	ft_strfreev(char **str_array);
int		ft_strlenv(char **str_array);

#endif
