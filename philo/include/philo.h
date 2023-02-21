/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:35:00 by jprofit           #+#    #+#             */
/*   Updated: 2023/01/30 18:57:42 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct timeval t_tval;

typedef enum e_action {
	EAT,
	FORK,
	SLEEP,
	THINK,
	DIED,
} t_action;

typedef struct s_env {
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int max_meal;
    int nb_dead;
	int ate_enough;
	int all_ate_enough;
	long long	start_time_ms;
	pthread_mutex_t	mutex_meal;
	pthread_mutex_t	*mutex_tab_fork;
	pthread_mutex_t	mutex_print;
}	t_env;

typedef struct s_philo {
	int			index;
	pthread_t	thread_id;
	t_env		*env;
	int 		right_fork_id;
	int 		left_fork_id;
	long long	last_meal;
	int 		nb_meal;
}	t_philo;

// INIT.C
int	write_error(void);
int fill_env(char **argv, int argc, t_env *env);
int	init_philo(t_env *env, t_philo **philo);

// UTILS.C

int	ft_atoi(const char *str);
long long	get_time_ms(void);
long long	get_time_since_ms(long long start_time);
void usleep_better(int usec);

// THREADS.C
int	create_threads(t_env *env, t_philo *philo);

// MUTEX.C
int		mutex_init(t_env *env);
void	destroy_mutex(t_env *env);

// PHILO_ACTIONS.C
int	check_dead(t_env *env, t_philo *philo);
void    print_action(t_env *env, t_philo *philo, t_action action);
int	check_all_eat(t_env *env, t_philo *philo);
void	philo_eat(t_env *env, t_philo *philo);

#endif
