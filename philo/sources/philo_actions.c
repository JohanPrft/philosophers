/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:19 by jprofit           #+#    #+#             */
/*   Updated: 2023/02/06 19:27:14 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_dead(t_rules *rules, t_philo *philo)
{
	if (get_time_ms() - philo->last_meal > rules->time_to_die)
	{
		philo->state = DEAD;
		pthread_mutex_lock(&rules->mutex_nb_dead);
		rules->nb_dead++;
		pthread_mutex_unlock(&rules->mutex_nb_dead);
	}
}

void	check_eat(t_rules *rules, t_philo *philo)
{
	if (rules->max_meal == -1)
		return;
	if (philo->nb_meal == rules->max_meal)
	{
		pthread_mutex_lock(&rules->mutex_eat);
		rules->ate_enough++;
		pthread_mutex_unlock(&rules->mutex_eat);
	}
	if (rules->max_meal == rules->nb_philo)
	{
		pthread_mutex_lock(&rules->mutex_eat);
		rules->all_ate_enough = 1;
		pthread_mutex_unlock(&rules->mutex_eat);
	}
}

void    action_and_print(t_rules *rules, t_philo *philo, char *action)
{
	if (!ft_strcmp(action, "is eating"))
	{
		pthread_mutex_lock(&rules->mutex_tab_fork[philo->right_fork_id]);
		printf("%lld %i has taken a fork (%i)\n", get_time_ms() - rules->start_time_ms, philo->index,philo->right_fork_id);
		pthread_mutex_lock(&rules->mutex_tab_fork[philo->left_fork_id]);
		printf("%lld %i has taken a fork (%i)\n", get_time_ms() - rules->start_time_ms, philo->index,philo->left_fork_id);
		printf("%lld %i is eating\n", get_time_ms() - rules->start_time_ms, philo->index);
		usleep_better(rules->time_to_eat);
		pthread_mutex_lock(&rules->mutex_eat);
		philo->last_meal = get_time_ms();
		philo->nb_meal++;
		pthread_mutex_unlock(&rules->mutex_eat);
		pthread_mutex_unlock(&rules->mutex_tab_fork[philo->right_fork_id]);
		pthread_mutex_unlock(&rules->mutex_tab_fork[philo->left_fork_id]);
	}
	else if (!ft_strcmp(action, "is sleeping"))
	{
		printf ("%lld %i %s\n", get_time_ms() - rules->start_time_ms, philo->index, action);
		usleep_better(rules->time_to_sleep);
	}
	else if (!ft_strcmp(action, "is thinking"))
	{
		printf ("%lld %i %s\n", get_time_ms() - rules->start_time_ms, philo->index, action);
		usleep_better(rules->time_to_eat);
	}
	else
		printf("error in action");
}
