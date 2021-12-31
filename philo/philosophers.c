/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:27:13 by arhallab          #+#    #+#             */
/*   Updated: 2021/12/28 12:55:59 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*test(void *i)
{
	static int	j = 1;

	j++;
	
	printf("%d %p\n", j, i);
	return(NULL);
}

int	main(int argc, char **argv)
{
	int			i;
	// int			j;
	t_philos	*philo;

	i = 0;
	if (argc < 5)
	{
		{
			printf ("%s : Not enough argument", argv[i]);
			return (-1);
		}
	}
	while (++i < argc - 1)
	{
		if (!isnum(argv[i]))
		{
			printf ("%s : Wrong argument", argv[i]);
			return (-1);
		}
	}
	philo = init_philo();
	philo->num_of_philos = ft_atopi(argv[1]);
	philo->philos = (pthread_t *)malloc(sizeof(pthread_t) * philo->num_of_philos);
	philo->time_to_die = ft_atopi(argv[2]);
	philo->time_to_eat = ft_atopi(argv[3]);
	philo->time_to_sleep = ft_atopi(argv[4]);
	philo->not_death_only = (argc == 6);
	(argc == 6) && (philo->eat_lim = ft_atopi(argv[5]));
	printf("lol\n");
	i = -1;
	while ((size_t)++i < philo->num_of_philos){
		pthread_create(&philo->philos[i], NULL, test, (void *)&philo->philos[i]);
		printf("Thread %d\n", i);}
	pthread_exit(NULL);
	return (0);
}
