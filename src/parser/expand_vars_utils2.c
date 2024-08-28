/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:51:04 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/28 10:58:16 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_sprintf(int *src_idx)
{
	char	*env_value;

	env_value = ft_strdup(ft_itoa(g_mini->exit_status));
	*src_idx += 1;
	return (env_value);
}

void	getenv_handler(char **env_value, int len, int *k)
{
	(*env_value) = (char *)malloc(len);
	(*env_value)[++(*k)] = '$';
}

char	*imp_while1(char *str, int *src_idx, int *var_idx)
{
	char	*env_value;
	char	var_name[100];
	int		j;
	int		k;

	while (str[(*src_idx)] && (ft_isalnum(str[(*src_idx)])
			|| str[(*src_idx)] == '_'))
	{
		var_name[(*var_idx)++] = str[(*src_idx)++];
		var_name[(*var_idx)] = '\0';
		env_value = find_var(var_name);
		if (env_value)
			break ;
	}
	var_name[(*var_idx)] = '\0';
	env_value = ((j = -1), (k = -1), NULL);
	env_value = find_var(var_name);
	if (!env_value)
	{
		getenv_handler(&env_value, ft_strlen(var_name), &k);
		while (var_name[++j])
			env_value[++k] = var_name[j];
		env_value[++k] = '\0';
	}
	return (env_value);
}

int	if_env(char *env_value, char *str, char **result, int *index)
{
	int	env_len;

	if (env_value)
	{
		env_len = ft_strlen(env_value);
		if (index[1] + env_len >= (int)ft_strlen(str) * 2)
		{
			(*result) = ft_realloc((*result), index[1] + env_len + 1);
			if (!(*result))
				return (0);
		}
		while (*env_value)
			(*result)[index[1]++] = *env_value++;
	}
	else
		(*result)[index[1]++] = str[index[0]++];
	return (index[1]);
}

void	manage_replacing(int *index, char *str, char **env_value)
{
	if (str[index[0]] == '?')
		(*env_value) = handle_sprintf(&index[0]);
	else
		(*env_value) = imp_while1(str, &index[0], &index[2]);
}
