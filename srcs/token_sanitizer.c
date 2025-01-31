/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_sanitizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:18:49 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/31 18:32:15 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#include "exec.h"

#include "libft.h"
#include <stdlib.h>

//function used to build up the string to be printed
char *concat_content(char *content, char *start, size_t i)
{
	char *buffer;
	char *tmp_content;
	
	buffer = ft_substr(start, 0, i);
	if (buffer == NULL)
		return (NULL);
	tmp_content = content;
	content = ft_strjoin(content, buffer);
	free(tmp_content);
	free(buffer);
	return (content);
}

//function extracts the variable name starting in var_start
//using get_env, the value of the variable is looked up
//function has 2 return values : var_name_len and the var_value 
char *expand_var(char *var_start, size_t *var_name_len, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	size_t	i;
	
	i = 0;
	while(ft_isalnum(var_start[i]) || var_start[i] == '_')
	{
		i++;
	}
	*var_name_len = i;
	var_name = ft_substr(var_start, 0, i);
	var_value = (char *)get_env(var_name, shell);
	free(var_name);
	if (var_value != NULL)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

//function used to remove quotes and expand variables
char *sanitize_token_content(char *line, char *end, t_shell *shell)
{
	size_t	i;
	size_t	var_name_len;
	char	*tmp;
	char	*start;
	char	*content;
	char	*var_value;
	bool	in_single;
	bool	in_double;
	
	i = 0;
	start = line;
	content = ft_strdup("");
	in_single = false;
	in_double = false;
	while ((line) + i != end && line[i] != '\0')
	{
		//marks end of substr as you either enter a single quoted str or you exit one.
		//checking that you are not inside a double quoted substr
		if (line[i] == '\'' && !in_double)
		{
			content = concat_content(content, start, &line[i] - start);
			in_single = !in_single;
			//move the start by 1 to exclude the single quote
			start = &line[i + 1]; 
			i++;
			continue;
		}
		if (line[i] == '\"' && !in_single)
		{
			content = concat_content(content, start, &line[i] - start);
			in_double = !in_double;
			//move the start by 1 to exclude the single quote
			start = &line[i + 1]; 
			i++;
			continue;
		}
		//concat content before $ to content, then retrieve the var_name for the expansion
		if (line[i] == '$' && line[i + 1] == '?' && !in_single)
		{
			content = concat_content(content, start, &line[i] - start);
			var_value = ft_itoa(shell->exit_status);
			tmp = content;
			content = ft_strjoin(content, var_value);
			free(tmp);
			free(var_value);
			i = i + 1;
			start = &line[i + 1];
			continue;
		}

		if (line[i] == '$' && !in_single)
		{
			content = concat_content(content, start, &line[i] - start);
			var_value = expand_var(&line[i + 1], &var_name_len, shell);
			tmp = content;
			content = ft_strjoin(content, var_value);
			free(tmp);
			free(var_value);
			i = i + var_name_len;
			start = &line[i + 1];
		}
		i++;
	}
	if (&line[i] - start > 0)
		content = concat_content(content, start, &line[i] - start);
	return (content);
}
