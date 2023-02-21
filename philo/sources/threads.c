/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:19 by jprofit           #+#    #+#             */
/*   Updated: 2023/02/06 11:27:14 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *void_philo)
{
	t_philo *philo;
	t_env	*env;

	philo = (t_philo *)void_philo;
	env = philo->env;
	pthread_mutex_lock(&env->mutex_meal);
	philo->last_meal = env->start_time_ms;
	pthread_mutex_unlock(&env->mutex_meal);
	if (philo->index % 2)
	{
		print_action(env, philo, THINK);
		usleep_better(100);
	}
	while (1)
	{
		philo_eat(env, philo);
		print_action(env, philo, SLEEP);
		usleep_better(env->time_to_sleep);
		print_action(env, philo, THINK);
	}
}

void exit_threads(t_env *rules, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philo[i].thread_id, NULL);
}

int	create_threads(t_env *env, t_philo *philo)
{
	int	i;

	i = -1;
	env->start_time_ms = get_time_ms();
	while (++i < env->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, &routine, (void *)&(philo[i])))
			return (0);
	}
	while (1)
	{
		if (check_dead(env, philo) == 1 || check_all_eat(env, philo) == 1)
			break;
	}
	return (1);
}
