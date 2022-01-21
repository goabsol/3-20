/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:19:58 by arhallab          #+#    #+#             */
/*   Updated: 2022/01/16 18:43:57 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atopi(const char *s)
{
	int				i;
	unsigned int	val;

	i = -1;
	val = 0;
	while (s[++i] != '\0')
	{
		if ((s[i] > '/' && s[i] < ':'))
		{
			while (s[i] > '/' && s[i] < ':')
			{
				val = val * 10 + s[i++] - 48;
			}
			return ((int)val);
		}
	}
	return ((int)val);
}

int	isnum(const char *s)
{
	while (*s)
	{
		if (*s > '9' || *s++ < '0')
			return (0);
	}
	return (1);
}
