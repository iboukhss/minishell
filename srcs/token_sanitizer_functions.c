/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sanitizer_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:37:55 by dheck             #+#    #+#             */
/*   Updated: 2025/02/11 14:37:58 by dheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#include "exec.h"

#include "libft.h"
#include <stdlib.h>

char	*handle_variable(char *content, char **start, char *c, t_shell *shell)
{
	char	*var_value;
	char	*tmp;
	size_t	var_name_len;

	content = concat_content(content, *start, c - *start);
	if (ft_isalnum(c[1]) == 0 && c[1] != '_')
	{
		content = concat_content(content, "$", 1);
		*start = c + 1;
		return (content);
	}
	var_value = expand_var(c + 1, &var_name_len, shell);
	tmp = content;
	content = ft_strjoin(content, var_value);
	free(tmp);
	free(var_value);
	*start = c + var_name_len + 1;
	return (content);
}

char	*handle_quotes(char *content, char **start, char *c, bool *quote_flag)
{
	content = concat_content(content, *start, c - *start);
	*quote_flag = !(*quote_flag);
	*start = c + 1;
	return (content);
}

char	*get_exit(char *content, char **start, char *c, t_shell *shell)
{
	char	*var_value;
	char	*tmp;

	content = concat_content(content, *start, c - *start);
	var_value = ft_itoa(shell->exit_status);
	if (!var_value)
		return (NULL);
	tmp = content;
	content = ft_strjoin(content, var_value);
	free(tmp);
	free(var_value);
	*start = c + 2;
	return (content);
}
