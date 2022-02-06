/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:27:13 by arhallab          #+#    #+#             */
/*   Updated: 2022/02/06 02:24:43 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_stuff(t_constraints *cons)
{
	int	i;

	if (pthread_mutex_init(&(cons->print), NULL) || !(++(cons->pass)))
		return (1);
	i = -1;
	while ((size_t)++i < cons->num_of_philos)
		if (pthread_mutex_init(&(cons->forks[i]), NULL) || !(++(cons->pass)))
			return (1);
	i = -1;
	while (i < 1)
	{
		while ((size_t)++i < cons->num_of_philos)
		{
			cons->philos[i] = init_philo(i, &cons);
			if (pthread_create(&cons->philos[i]->philo,
					NULL, routine, &cons->philos[i]))
				return (1);
			i++;
		}
		usleep(100);
		i = i % 2;
	}
	return (0);
}

static int	bigbrother(t_constraints *cons)
{
	t_time	t;
	int		i;

	while (!cons->ded && cons->done != cons->num_of_philos && !cons->sysfail)
	{
		usleep(1000);
		i = -1;
		while ((size_t)++i < cons->num_of_philos)
		{
			gettimeofday(&t, NULL);
			if (cons->done == cons->num_of_philos)
				break ;
			if ((size_t)(timestitch(t) - cons->philos[i]->last_meal)
				>= cons->time_to_die)
			{
				cons->ded = 1;
				printf("%ld philo %d died\n", timestitch(t), i + 1);
				break ;
			}
		}
	}
	if (cons->sysfail)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int				i;
	t_constraints	*cons;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf ("%s : Not enough argument\n", argv[i]);
		return (-1);
	}
	while (++i < argc)
	{
		if (!isnum(argv[i]))
		{
			printf ("%s : Wrong argument\n", argv[i]);
			return (-1);
		}
	}
	cons = init_cons(argc, argv);
	if (!cons || cons->sysfail)
		return (wiseness_free(cons, -1));
	if (init_stuff(cons))
		return (wiseness_free(cons, -1));
	if (bigbrother(cons))
		return (wiseness_free(cons, -1));
	return (wiseness_free(cons, 0));
}
