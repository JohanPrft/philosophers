/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:50:52 by jprofit           #+#    #+#             */
/*   Updated: 2023/02/24 11:50:52 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_env *env, t_philo *philo)
{
	printf("philo %i wait for lock right %i\n", philo->index, philo->right_fork_id);
	pthread_mutex_lock(&env->mutex_tab_fork[philo->right_fork_id - 1]);
	print_action(env, philo, FORK);
	printf("philo %i wait for lock left %i\n", philo->index, philo->left_fork_id);
	pthread_mutex_lock(&env->mutex_tab_fork[philo->left_fork_id - 1]);
	print_action(env, philo, FORK);
	print_action(env, philo, EAT);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mutex_meal);
	usleep_better(env->time_to_eat);
	philo->nb_meal++;
	pthread_mutex_unlock(&env->mutex_tab_fork[philo->right_fork_id - 1]);
	pthread_mutex_unlock(&env->mutex_tab_fork[philo->left_fork_id - 1]);
}

void    print_action(t_env *env, t_philo *philo, t_action action)
{
	static char *tab_action[] = {"is eating", "has taken a fork", "is sleeping", "is thinking", "died"};

	pthread_mutex_lock(&env->mutex_print);
	printf("%lld %i %s\n", get_time_ms() - env->start_time_ms, philo->index, tab_action[action]);
//	if (action != DIED)
	pthread_mutex_unlock(&env->mutex_print);
}