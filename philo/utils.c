/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:19:58 by arhallab          #+#    #+#             */
/*   Updated: 2021/12/25 18:37:58 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philos	*init_philo(void)
{
	t_philos	*new;

	new = (t_philos *)malloc(sizeof(t_philos));
	return (new);
}

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
