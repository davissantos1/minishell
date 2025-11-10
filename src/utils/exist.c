/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitosant <vitosant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:28:33 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/10 18:10:33 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' )
		return (1);
	else if (c == '\n' || c == '\r' || c == '\v')
		return (1);
	else if (c == '\0')
		return (1);
	else
		return (0);
}

int	is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	else if (c == '(' || c == ')' || c == '~' || c == '-')
		return (1);
	else if (c == '*' || c == ':' || c == '.' || c == '/')
		return (1);
	else if (c == '\\' || c == '?' || c == '#' || c == '@')
		return (1);
	else if (c == '^' || c == '%' || c == '`' || c == '+')
		return (1);
	else if (c == ';' || c == ',' || c == '[' || c == ']')
		return (1);
	else if (c == '{' || c == '}' || c == '!')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}
