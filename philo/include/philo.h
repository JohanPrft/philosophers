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

typedef struct s_rules {
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_rules;

typedef struct s_philo {
	int			index;
	t_rules		*param;
	t_tval		time;
}	t_philo;

// INIT.C
int	write_error(void);
int	fill_struct(int argc, char **argv, t_rules *param);
int	init_philo(t_rules *rules, t_philo *philo);

// UTILS.C

int	ft_atoi(const char *str);

#endif
