/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:35:00 by jprofit           #+#    #+#             */
/*   Updated: 2023/02/24 13:50:48 by jprofit          ###   ########.fr       */
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

# define ERROR 1
# define SUCCESS 0
# define STDERR 2
# define STR_ERR_SYNTAX "Wrong syntax : please start the program as follow : ./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> (<max_nb_eat>)"
# define STR_ERR_MALLOC "Memory allocation failed"
# define STR_ERR_MUTEX "Initialisation of a mutex failed"
# define STR_ERR_THREAD "Creation of a thread failed"

typedef struct timeval t_tval;
typedef struct s_env t_env;
typedef struct s_philo t_philo;

typedef enum e_action {
	EAT,
	FORK,
	SLEEP,
	THINK,
	DIED,
} t_action;

struct s_env {
	int	nb_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int max_meal;
	int stop_simulation;
	time_t	start_time_ms;
	pthread_mutex_t mutex_print;
	pthread_mutex_t *mutex_tab_fork;
	pthread_mutex_t mutex_stop_simu;
	t_philo *philo;
};

struct s_philo {
	t_env		*env;
	int			index;
	int 		right_fork_id;
	int 		left_fork_id;
	pthread_mutex_t mutex_meal;
	time_t	last_meal;
	int 		nb_meal;
	pthread_t	thread_id;
};

// UTILS
int	ft_atoi(const char *str);
long long	get_time_ms(void);
void usleep_better(time_t usec);
void	clean(t_env *env);

// PARSING
int parsing(char **argv, int argc, t_env *env);

// INIT
int	write_error(char *str, t_env *env);
int	init_philo(t_env *env, t_philo **philo);

// PHILOSOPHERS
void	start_synchro(long long start_time);
void	*philosopher(void *philo_void);

// PHILO_ACTION
void	philo_eat(t_env *env, t_philo *philo);
void    print_action(t_env *env, t_philo *philo, t_action action);

// HITMAN
int	stop_simulation(t_env *env , bool flag);


#endif
