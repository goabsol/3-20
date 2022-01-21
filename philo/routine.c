/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:08:05 by arhallab          #+#    #+#             */
/*   Updated: 2022/01/21 15:08:42 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	loop(t_philos *philo, t_time t)
{
	pthread_mutex_lock(&(philo->cons->forks[(philo->id + 1)
			% philo->cons->num_of_philos]));
	if (main_printf("%ld philo %d has taken a fork\n", t, philo))
		return (1);
	pthread_mutex_lock(&(philo->cons->forks[philo->id]));
	if (main_printf("%ld philo %d has taken a fork\n", t, philo))
		return (1);
	gettimeofday(&t, NULL);
	philo->last_meal = timestitch(t);
	if (main_printf("%ld philo %d is eating\n", t, philo))
		return (1);
	isleep(philo->cons->time_to_eat * 1000);
	pthread_mutex_unlock(&(philo->cons->forks[philo->id]));
	pthread_mutex_unlock(&(philo->cons->forks[(philo->id + 1)
			% philo->cons->num_of_philos]));
	if (main_printf("%ld philo %d is sleeping\n", t, philo))
		return (1);
	isleep(philo->cons->time_to_sleep * 1000);
	if (main_printf("%ld philo %d is thinking\n", t, philo))
		return (1);
	return (0);
}

void	*routine(void *i)
{
	t_philos	*philo;
	t_time		t;

	philo = *(t_philos **)i;
	gettimeofday(&t, NULL);
	philo->last_meal = timestitch(t);
	while (philo->cons->num_of_philos > 1)
		if (loop(philo, t))
			return (NULL);
	return (NULL);
}
