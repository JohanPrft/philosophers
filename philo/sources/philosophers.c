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

void	alone_philo(t_env *env, t_philo *philo)
{
	print_action(env, philo, THINK);
	while (!stop_simulation(env, false))
		usleep_better(100);
}

void	set_last_meal (t_env *env, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = env->start_time_ms;
	pthread_mutex_unlock(&philo->mutex_meal);
}

void	*philosopher(void *philo_void)
{
	t_philo	*philo;
	t_env	*env;

	philo = philo_void;
	env = philo->env;
	set_last_meal(env, philo);
	start_synchro(env->start_time_ms);
	if (env->nb_philo == 1)
	{
		alone_philo(env, philo);
		return (NULL);
	}
	if (philo->index % 2)
	{
		print_action(env, philo, THINK);
		usleep_better(100);
	}
	while (!stop_simulation(env, false))
	{
		philo_eat(env, philo);
		print_action(env, philo, SLEEP);
		usleep_better(env->time_to_sleep);
		print_action(env, philo, THINK);
	}
	return (NULL);
}