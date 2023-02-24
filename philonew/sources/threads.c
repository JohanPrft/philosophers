/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:02:45 by jprofit           #+#    #+#             */
/*   Updated: 2023/02/22 18:02:45 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
 * keep the program until start_time is reached
 */
void	start_synchro(long long start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}

/*
 * protect the stop_simulation variable
 * copying the stop_simulation var is necessary in order to protect it
 * return a bool
 */
int	stop_simulation(t_env *env)
{
	int temp;

	pthread_mutex_lock(&env->mutex_stop_simu);
	temp = env->stop_simulation;
	pthread_mutex_unlock(&env->mutex_stop_simu);
	return (temp);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;
	t_env	*env;

	philo = philo_void;
	env = philo->env;
	philo->last_meal = env->start_time_ms;
	start_synchro(env->start_time_ms);
	if (philo->index % 2)
	{
		print_action(env, philo, THINK);
		usleep_better(100);
	}
//	while (!stop_simulation(env))
//	{
		philo_eat(env, philo);
		usleep_better(env->time_to_eat);
//	}
	return (NULL);
}