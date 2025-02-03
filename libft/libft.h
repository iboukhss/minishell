/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:40:51 by dheck             #+#    #+#             */
/*   Updated: 2025/02/03 16:59:14 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stddef.h>

// Standard libc functions
char	*ft_strchr(const char *s, int c);
char	*ft_strchrnul(const char *s, int c);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalnum(int c);

// Print functions
int		ft_printf(const char *fmt, ...);
int		ft_dprintf(int fd, const char *fmt, ...);
int		ft_vdprintf(int fd, const char *fmt, va_list ap);
int		ft_snprintf(char *s, size_t n, const char *fmt, ...);
int		ft_vsnprintf(char *s, size_t n, const char *fmt, va_list ap);
void	log_error(const char *fmt, ...);

// Fail-safe alloc functions
void	*ft_xmalloc(size_t size);
char	*ft_xstrdup(const char *s);

// String array functions (glib)
char	**ft_xstrdupv(char **str_array);
void	ft_strfreev(char **str_array);
int		ft_strv_length(char **str_array);

#endif
