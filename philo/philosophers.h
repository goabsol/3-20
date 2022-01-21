/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 15:27:32 by arhallab          #+#    #+#             */
/*   Updated: 2022/01/21 15:09:05 by arhallab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval			t_time;

typedef struct s_constraints	t_constraints;

typedef struct s_philos			t_philos;

typedef struct s_msg			t_msg;

struct	s_constraints
{
	size_t			num_of_philos;
	t_philos		**philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	int				*test;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			eat_lim;
	int				ded;
	int				not_death_only;
	t_msg			*msg;
	int				firstmsg;
};

struct	s_philos
{
	int				id;
	pthread_t		philo;
	long			last_meal;
	int				eatin;
	t_constraints	*cons;
};

struct	s_msg
{
	char	*msg;
	long	t;
	int		id;
	t_msg	*next;
};

t_philos		*init_philo(int i, t_constraints **cons);
t_constraints	*init_cons(int argc, char **argv);
int				ft_atopi(const char *s);
int				isnum(const char *s);
int				main_printf(char *s, t_time tt, t_philos *philo);
long			timestitch(t_time t);
int				isleep(size_t n);
t_msg			*newmsg(char *msg, long t, int id);
int				msgadd(t_msg **msg, t_msg *nmsg);
void			printmsg(t_msg **msg, t_constraints *cons);
int				loop(t_philos *philo, t_time t);
void			*routine(void *i);

#endif