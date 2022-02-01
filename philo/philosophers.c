/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:27:13 by arhallab          #+#    #+#             */
/*   Updated: 2022/02/01 06:20:52 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_stuff(t_constraints *cons)
{
	int	i;

	pthread_mutex_init(&(cons->print), NULL);
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
	t_time	t;
	int		i;

	while (!cons->ded && cons->done != cons->num_of_philos && !cons->sysfail)
	{
		usleep(100);
		i = -1;
		while ((size_t)++i < cons->num_of_philos)
		{
			gettimeofday(&t, NULL);
			if (cons->done == cons->num_of_philos)
				break ;
			if ((size_t)(timestitch(t) - cons->philos[i]->last_meal)
				> cons->time_to_die)
			{
				cons->ded = 1;
				printf("%ld philo %d died\n", timestitch(t), i);
				break ;
			}
		}
	}
}

static void	finish_stuff(t_constraints *cons)
{
	int	i;

	i = -1;
	while ((size_t)++i < cons->num_of_philos)
	{
		pthread_join(cons->philos[i]->philo, NULL);
		free(cons->philos[i]);
	}
	free(cons->philos);
	i = -1;
	while ((size_t)++i < cons->num_of_philos)
	{
		pthread_mutex_destroy(&(cons->forks[i]));
	}
	free(cons->forks);
	pthread_mutex_destroy(&(cons->print));
	free(cons);
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	int				i;
	t_constraints	*cons;

	i = 0;
	if (argc < 5)
	{
		printf ("%s : Not enough argument\n", argv[i]);
		return (-1);
	}
	while (++i < argc)
	{
		printf ("%d====>%s\n", argc, argv[i]);
		if (!isnum(argv[i]))
		{
			printf ("%s : Wrong argument\n", argv[i]);
			return (-1);
		}
	}
	cons = init_cons(argc, argv);
	init_stuff(cons);
	bigbrother(cons);
	finish_stuff(cons);
	return (0);
}
