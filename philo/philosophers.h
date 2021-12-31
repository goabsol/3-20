/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:27:32 by arhallab          #+#    #+#             */
/*   Updated: 2021/12/28 12:49:40 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philos	t_philos;

struct	s_philos
{
	size_t		num_of_philos;
	pthread_t	*philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		eat_lim;
	int			not_death_only;
};

t_philos	*init_philo(void);
int			ft_atopi(const char *s);
int			isnum(const char *s);

#endif