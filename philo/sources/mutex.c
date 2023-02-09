/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c      	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by jprofit           #+#    #+#             */
/*   Updated: 2023/02/06 17:27:14 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void destoy_mutex_tab(pthread_mutex_t *mutex_tab_fork, int max)
{
	int	i;

	i = -1;
	while (++i < max)
		pthread_mutex_destroy(&mutex_tab_fork[i]);
}

int	mutex_init(t_env *env)
{
	int i;
	if (pthread_mutex_init(&env->mutex_nb_dead, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&env->mutex_eat, NULL) != 0)
	{
		pthread_mutex_destroy(&env->mutex_nb_dead);
		return (0);
	}
	pthread_mutex_init(&env->mutex_print, NULL);
	i = -1;
	while (++i < env->nb_philo)
	{
		pthread_mutex_t *mutex_tab_fork = env->mutex_tab_fork;
		if (pthread_mutex_init(&mutex_tab_fork[i], NULL) != 0)
		{
			pthread_mutex_destroy(&env->mutex_nb_dead);
			pthread_mutex_destroy(&env->mutex_eat);
			destoy_mutex_tab(mutex_tab_fork, i);
			return (0);
		}
	}
	return (1);
}

void	destroy_mutex(t_env *env)
{
	pthread_mutex_destroy(&env->mutex_nb_dead);
	pthread_mutex_destroy(&env->mutex_eat);
	pthread_mutex_destroy(&env->mutex_print);
	destoy_mutex_tab(env->mutex_tab_fork, env->nb_philo);
}
