/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:08:05 by arhallab          #+#    #+#             */
/*   Updated: 2022/02/03 15:13:15 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	fork_lift(t_philos *philo, t_time t)
{
	if (pthread_mutex_lock(&(philo->cons->forks[(philo->id + 1)
					% philo->cons->num_of_philos])))
		return (philo->cons->sysfail = 1);
	if (main_printf("%ld philo %d has taken a fork\n", t, philo))
		return (1);
	if (pthread_mutex_lock(&(philo->cons->forks[philo->id])))
		return (philo->cons->sysfail = 1);
	if (main_printf("%ld philo %d has taken a fork\n", t, philo))
		return (1);
	return (0);
}

static int	fork_unlift(t_philos *philo)
{
	if (pthread_mutex_unlock(&(philo->cons->forks[philo->id])))
		return (philo->cons->sysfail = 1);
	if (pthread_mutex_unlock(&(philo->cons->forks[(philo->id + 1)
					% philo->cons->num_of_philos])))
		return (philo->cons->sysfail = 1);
	return (0);
}

static int	loop(t_philos *philo, t_time t)
{
	if (fork_lift(philo, t))
		return (1);
	gettimeofday(&t, NULL);
	philo->last_meal = timestitch(t);
	if (main_printf("%ld philo %d is eating\n", t, philo))
		return (1);
	isleep(philo->cons->time_to_eat * 1000);
	philo->cons->not_death_only && philo->eat_lim--;
	if (fork_unlift(philo))
		return (1);
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
	while (philo->cons->num_of_philos > 1
		&& philo->cons->done != philo->cons->num_of_philos)
	{
		if (loop(philo, t))
			return (NULL);
		if (!philo->eat_lim)
			philo->cons->done++;
	}
	return (NULL);
}
