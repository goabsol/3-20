/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:27:13 by arhallab          #+#    #+#             */
/*   Updated: 2022/01/21 15:12:31 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_stuff(t_constraints *cons)
{
	int	i;

	i = -1;
	while ((size_t)++i < cons->num_of_philos)
	{
		pthread_mutex_init(&(cons->forks[i]), NULL);
	}
	i = -1;
	while ((size_t)++i < cons->num_of_philos)
	{
		cons->philos[i] = init_philo(i, &cons);
		pthread_create(&cons->philos[i]->philo,
			NULL, routine, &cons->philos[i]);
		i++;
	}
	usleep(1000);
	i = 0;
	while ((size_t)++i < cons->num_of_philos)
	{
		cons->philos[i] = init_philo(i, &cons);
		pthread_create(&cons->philos[i]->philo,
			NULL, routine, &cons->philos[i]);
		i++;
	}
}

static void	bigbrother(t_constraints *cons)
{
	t_msg	*msg;
	t_time	t;
	int		i;

	msg = cons->msg;
	while (!cons->ded)
	{
		usleep(100);
		i = -1;
		while ((size_t)++i < cons->num_of_philos)
		{
			gettimeofday(&t, NULL);
			if ((size_t)(timestitch(t) - cons->philos[i]->last_meal)
				> cons->time_to_die)
			{
				cons->ded = 1;
				printf("%ld philo %d died\n", timestitch(t), i);
				break ;
			}
			printmsg(&msg, cons);
		}
	}
}

static void	finish_stuff(t_constraints *cons)
{
	int	i;

	i = -1;
	while ((size_t)++i < cons->num_of_philos)
		pthread_join(cons->philos[i]->philo, NULL);
	i = -1;
	while ((size_t)++i < cons->num_of_philos)
		pthread_mutex_destroy(&(cons->forks[i]));
	pthread_mutex_destroy(&(cons->print));
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	int				i;
	t_constraints	*cons;

	i = 0;
	if (argc < 5)
	{
		printf ("%s : Not enough argument", argv[i]);
		return (-1);
	}
	while (++i < argc - 1)
	{
		if (!isnum(argv[i]))
		{
			printf ("%s : Wrong argument", argv[i]);
			return (-1);
		}
	}
	cons = init_cons(argc, argv);
	init_stuff(cons);
	bigbrother(cons);
	finish_stuff(cons);
	return (0);
}
