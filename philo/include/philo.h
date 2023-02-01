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

typedef enum e_state {
	INIT = -1,
	DEAD = 0,
	THINK = 1,
	EAT = 2,
	SLEEP = 3,
} t_state;

typedef struct s_rules {
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int max_meal;
}	t_rules;

typedef struct s_philo {
	int			index;
	pthread_t	thread_id;
	t_rules		*param;
	t_state		state;
	int 		right_fork_id;
	int 		left_fork_id;
	long long	last_meal;
}	t_philo;

// INIT.C
int	write_error(void);
int fill_rules(char **argv, int argc, t_rules *param);
int	init_philo(t_rules *rules, t_philo **philo);

// UTILS.C

int	ft_atoi(const char *str);
long long	get_time_ms(void);
long long	time_diff_ms(long long last, long long now);


// THREADS.C
int	create_threads(t_rules *rules, t_philo *philo);

#endif
