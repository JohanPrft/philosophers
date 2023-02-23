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

# define ERR 1
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
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int max_meal;
	int one_dead;
	long long	start_time_ms;
	pthread_mutex_t mutex_print;
	t_philo *philo;
};

struct s_philo {
	t_env		*env;
	int			index;
	int 		right_fork_id;
	int 		left_fork_id;
	long long	last_meal;
	int 		nb_meal;
	pthread_t	thread_id;
};

// UTILS
int	ft_atoi(const char *str);
long long	get_time_ms(void);
void usleep_better(int usec);
int ft_strcmp(const char *str1, const char *str2);

// PARSING
int parsing(char **argv, int argc, t_env *env);

// INIT
int	write_error(char *str, t_env *env);
int	init_philo(t_env *env, t_philo **philo);

// THREADS
void	start_synchro(long long start_time);
void	*routine(void *philo_void);


#endif
