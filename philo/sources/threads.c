/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:19 by jprofit           #+#    #+#             */
/*   Updated: 2023/02/22 10:35:22 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	sleep_until_go(long long start_time_ms)
{
	while(start_time_ms > get_time_ms())
		continue;
}

void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)void_philo;
	env = philo->env;
	if (env->max_meal == 0)
		return (NULL);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = env->start_time_ms;
	pthread_mutex_unlock(&philo->mutex_meal);
	sleep_until_go(env->start_time_ms);
	if (philo->index % 2)
	{
		print_action(env, philo, THINK);
		usleep_better(100);
	}
	while (has_simulation_stopped(philo->table) == false)
	{
		philo_eat(env, philo);
		print_action(env, philo, SLEEP);
		usleep_better(env->time_to_sleep);
		print_action(env, philo, THINK);
	}
	return (NULL);
}

int	create_threads(t_env *env, t_philo *philo)
{
	int i;

	env->start_time_ms = get_time_ms() + (env->nb_philo * 2 * 10);
	i = -1;
	while (++i < env->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, &routine, (void *)&(philo[i])))
			return (false);
	}
	usleep_better(1000);
	return (1);
}