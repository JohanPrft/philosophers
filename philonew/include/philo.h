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
# include <stdbool.h>
# include <sys/time.h>

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
}	t_env;

typedef struct s_philo {
	t_env		*env;
	int			index;
	int 		right_fork_id;
	int 		left_fork_id;
	long long	last_meal;
	int 		nb_meal;
}	t_philo;

// UTILS
int	ft_atoi(const char *str);
long long	get_time_ms(void);
void usleep_better(int usec);
int ft_strcmp(const char *str1, const char *str2);

// INIT
int	write_error(void);
int fill_env(char **argv, int argc, t_env *env);
int	init_philo(t_env *env, t_philo **philo);

#endif