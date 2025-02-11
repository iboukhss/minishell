/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sanitizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:18:49 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/11 10:09:18 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#include "exec.h"

#include "libft.h"
#include <stdlib.h>

//function used to build up the string to be printed
char	*concat_content(char *content, char *start, size_t i)
{
	char	*buffer;
	char	*tmp_content;

	buffer = ft_substr(start, 0, i);
	if (buffer == NULL)
		return (NULL);
	tmp_content = content;
	content = ft_strjoin(content, buffer);
	free (tmp_content);
	free (buffer);
	return (content);
}

//function extracts the variable name starting in var_start
//using get_env, the value of the variable is looked up
//function has 2 return values : var_name_len and the var_value 
char	*expand_var(char *var_start, size_t *var_name_len, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	size_t	i;

	i = 0;
	while (ft_isalnum(var_start[i]) || var_start[i] == '_')
	{
		i++;
	}
	*var_name_len = i;
	var_name = ft_substr(var_start, 0, i);
	var_value = (char *)get_env(var_name, shell);
	free (var_name);
	if (var_value != NULL)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

char	*handle_variable(char *content, char **start, char *c, t_shell *shell)
{
	char	*var_value;
	char	*tmp;
	size_t	var_name_len;

	content = concat_content(content, *start, c - *start);
	var_value = expand_var(c + 1, &var_name_len, shell);
	tmp = content;
	content = ft_strjoin(content, var_value);
	free(tmp);
	free(var_value);
	*start = c + var_name_len + 1;
	return (content);
}

void	init_variables(char *line, char **start, char **content, size_t *i)
{
	*i = 0;
	*start = line;
	*content = ft_strdup("");
}

void	init_bool(bool *in_single, bool*in_double)
{
	*in_single = false;
	*in_double = false;
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

//function used to remove quotes and expand variables
char	*sanitize_token_content(char *line, char *end, t_shell *shell)
{
	size_t	i;
	char	*start;
	char	*content;
	bool	in_single;
	bool	in_double;

	init_variables(line, &start, &content, &i);
	init_bool(&in_single, &in_double);
	while (line + i != end && line[i] != '\0')
	{
		if (line[i] == '\'' && !in_double)
			content = handle_quotes(content, &start, line + i, &in_single);
		else if (line[i] == '\"' && !in_single)
			content = handle_quotes(content, &start, line + i, &in_double);
		else if (line[i] == '$' && line[i + 1] == '?' && !in_single)
			content = get_exit(content, &start, line + i, shell);
		else if (line[i] == '$' && !in_single)
			content = handle_variable(content, &start, line + i, shell);
		i++;
	}
	if (&line[i] - start > 0)
		content = concat_content(content, start, &line[i] - start);
	return (content);
}
