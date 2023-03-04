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
 * wait until start_time is reached
 */
void	start_synchro(long long start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}

/*
 * needed for the philo to not be stuck with a fork and waiting forever
 * for one that doesnt exist
 */
void	*alone_philo(t_env *env, t_philo *philo)
{
	print_action(env, philo, THINK, false);
	while (!stop_simulation(env, false))
		usleep_better(100);
	return (NULL);
}

void	set_last_meal(t_env *env, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = env->start_time_ms;
	pthread_mutex_unlock(&philo->mutex_meal);
}

/*
 * philosophers will live when start_time_ms will be reached (leaving time
 * for all of them and the hitman to be set up)
 * odd philo will start to thing to avoid chaos when they start to live
 * if the number of philo is odd a small time to sleep is imposed to prevent
 * them to eat (uselessly) again
 */
void	*philosopher(void *philo_void)
{
	t_philo	*philo;
	t_env	*env;

	philo = philo_void;
	env = philo->env;
	set_last_meal(env, philo);
	start_synchro(env->start_time_ms);
	if (env->nb_philo == 1)
		return (alone_philo(env, philo));
	if (philo->index % 2)
	{
		print_action(env, philo, THINK, 0);
		usleep_better(100);
	}
	while (!stop_simulation(env, false))
	{
		philo_eat(env, philo);
		print_action(env, philo, SLEEP, false);
		usleep_better(env->time_to_sleep);
		print_action(env, philo, THINK, false);
		if (env->nb_philo % 2 == 1)
			usleep_better(env->time_to_die / env->nb_philo);
	}
	return (NULL);
}
