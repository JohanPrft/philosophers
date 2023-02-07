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
		pthread_mutex_lock(&rules->mutex_nb_dead);
		rules->ate_enough++;
		pthread_mutex_unlock(&rules->mutex_nb_dead);
	}
}

void    action_and_print(t_rules *rules, int nb_philo, char *action, int time)
{
	printf ("%lld %i %s\n", get_time_ms() - rules->start_time_ms, nb_philo, action);
	usleep_better(time);
}

