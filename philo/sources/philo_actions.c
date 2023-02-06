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

void	check_dead(t_rules *rules, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
	{
		if (philo[i]->state == DEAD)
		{
			pthread_mutex_lock(&rules->mutex_nb_dead);
			rules->nb_dead++;
			pthread_mutex_unlock(&rules->mutex_nb_dead);
		}
	}
}

void    action_and_print(t_rules *rules, int nb_philo, char *action, int time)
{
	printf ("%lld %i %s\n", get_time_ms() - rules->start_time_ms, nb_philo, action);
	usleep_better(time);
}

