/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:50:52 by jprofit           #+#    #+#             */
/*   Updated: 2023/03/02 14:35:59 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_env *env, t_philo *philo)
{
	if (env->nb_philo == 1)
		return ;
	pthread_mutex_lock(&env->mutex_tab_fork[philo->right_fork_id - 1]);
	print_action(env, philo, FORK, 0);
	pthread_mutex_lock(&env->mutex_tab_fork[philo->left_fork_id - 1]);
	print_action(env, philo, FORK, 0);
	print_action(env, philo, EAT, 0);
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->mutex_meal);
	usleep_better(env->time_to_eat);
	philo->nb_meal++;
	is_philo_full(env, philo);
	pthread_mutex_unlock(&env->mutex_tab_fork[philo->right_fork_id - 1]);
	pthread_mutex_unlock(&env->mutex_tab_fork[philo->left_fork_id - 1]);
}

void	print_action(t_env *env, t_philo *philo, t_action action, bool died)
{
	static char	*tab_action[] = \
	{"is eating", "has taken a fork", "is sleeping", "is thinking", "died"};

	pthread_mutex_lock(&env->mutex_print);
	if (stop_simulation(env, false) == true && died == false)
	{
		pthread_mutex_unlock(&env->mutex_print);
		return ;
	}
	printf("%li %i %s\n", \
	get_time_ms() - env->start_time_ms, philo->index, tab_action[action]);
	pthread_mutex_unlock(&env->mutex_print);
}
