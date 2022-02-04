/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 18:42:47 by arhallab          #+#    #+#             */
/*   Updated: 2022/02/03 15:17:56 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main_printf(char *s, t_time tt, t_philos *philo)
{
	long			t;
	t_constraints	*c;

	gettimeofday(&tt, NULL);
	t = timestitch(tt);
	c = philo->cons;
	if (pthread_mutex_lock(&(c->print)))
		return (c->sysfail = 1);
	if (c->ded)
	{
		c->sysfail = pthread_mutex_unlock(&(c->forks[philo->id]))
			+ pthread_mutex_unlock(&(c->forks[(philo->id + 1)
					% c->num_of_philos]))
			+ pthread_mutex_unlock(&(c->print));
		return (1);
	}
	printf(s, t, philo->id);
	if (pthread_mutex_unlock(&(c->print)))
		return (c->sysfail = 1);
	return (0);
}

t_constraints	*init_cons(int argc, char **argv)
{
	t_constraints	*new;

	new = (t_constraints *)malloc(sizeof(t_constraints));
	if (!new)
		return (NULL);
	new->pass = 1;
	new->num_of_philos = ft_atopi(argv[1]);
	new->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* new->num_of_philos);
	if ((!(new->forks) && ++new->sysfail) || !(++(new->pass)))
		return (new);
	new->philos = (t_philos **)malloc(sizeof(t_philos *)
			* new->num_of_philos);
	if ((!(new->philos) && ++new->sysfail) || !(++(new->pass)))
		return (new);
	new->time_to_die = ft_atopi(argv[2]);
	new->time_to_eat = ft_atopi(argv[3]);
	new->time_to_sleep = ft_atopi(argv[4]);
	new->not_death_only = (argc == 6);
	new->done = 0;
	new->eat_lim = -1;
	(argc == 6) && (new->eat_lim = ft_atopi(argv[5]));
	new->ded = 0;
	new->sysfail = 0;
	return (new);
}

t_philos	*init_philo(int i, t_constraints **cons)
{
	t_philos	*new;

	new = (t_philos *)malloc(sizeof(t_philos));
	if (!new || !(((*cons)->pass)++))
		return (NULL);
	new->id = i;
	new->eatin = 0;
	new->cons = *cons;
	new->eat_lim = (*cons)->eat_lim;
	return (new);
}

long	timestitch(t_time t)
{
	long	r;

	r = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (r);
}

int	isleep(size_t n)
{
	t_time	t;
	t_time	f;

	gettimeofday(&t, NULL);
	while (1)
	{
		gettimeofday(&f, NULL);
		if ((size_t)(f.tv_usec - t.tv_usec) >= n)
			break ;
		usleep(100);
	}
	return (0);
}
