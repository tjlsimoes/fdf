/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:01:45 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/09/23 10:51:12 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_uppercase_q(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

static int	get_idx(char c)
{
	char	*hex_base_chars;
	int		i;

	i = 0;
	hex_base_chars = "0123456789abcdef";
	while (hex_base_chars[i])
	{
		if (hex_base_chars[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	valid_string(char *str, int str_base)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (get_idx(str[i]) >= str_base)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_rgb(char *str, int str_base)
{
	int	nbr;
	int	i;

	if (!str || !str_base)
		return (0);
	if (!valid_string(str, str_base))
		return (0);
	nbr = 0;
	i = 0;
	if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	while (str[i] && ft_isalnum(str[i]))
	{
		if (is_uppercase_q(str[i]))
			nbr = str_base * nbr + (get_idx(str[i] + 32));
		else
			nbr = str_base * nbr + (get_idx(str[i]));
		i++;
	}
	return (nbr);
}
