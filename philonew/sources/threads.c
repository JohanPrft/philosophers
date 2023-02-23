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

void	start_synchro(long long start_time)
{
	while (get_time_ms() < start_time)
		continue ;
}

void	*routine(void *philo_void)
{
	t_philo	*philo;
	t_env	*env;

	philo = philo_void;
	env = philo->env;
	philo->last_meal = env->start_time_ms;
	start_synchro(env->start_time_ms);
	printf("philo n%i : ate at %lld", philo->index, philo->last_meal);
	return (NULL);
}