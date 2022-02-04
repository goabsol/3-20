/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:19:58 by arhallab          #+#    #+#             */
/*   Updated: 2022/02/03 15:53:04 by arhallab         ###   ########.fr       */
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

int	wiseness_free(t_constraints *cons, int ret)
{
	while (cons && cons->pass > 0)
	{
		if (!(cons->pass - 2))
			free(cons->forks);
		if (!(cons->pass - 3))
			free(cons->philos);
		if (!(cons->pass - 4))
			pthread_mutex_destroy(&(cons->print));
		if (cons->pass < 4 + cons->num_of_philos && cons->pass > 4)
			pthread_mutex_destroy(&(cons->forks[cons->pass - 4]));
		if (cons->pass > 4 + cons->num_of_philos
			&& cons->pass < 4 + 2 * cons->num_of_philos)
		{
			free(cons->philos[cons->pass - 4 - cons->num_of_philos]);
			pthread_join(cons->philos
			[cons->pass - 4 - cons->num_of_philos]->philo, NULL);
		}
		cons->pass--;
		if (!(cons->pass))
			free(cons);
	}
	if (ret == -1)
		printf("something went wrong ¯\\_(ツ)_/¯");
	return (ret);
}
