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

int	mutex_init(t_rules *rules)
{
	if (pthread_mutex_init(&rules->mutex_nb_dead, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&rules->mutex_rfork, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->mutex_nb_dead);
		return (0);
	}
	if (pthread_mutex_init(&rules->mutex_lfork, NULL) != 0)
	{
		pthread_mutex_destroy(&rules->mutex_nb_dead);
		pthread_mutex_destroy(&rules->mutex_rfork);
		return (0);
	}
	return (1);
}

void	destroy_mutex(t_rules *rules)
{
	pthread_mutex_destroy(&rules->mutex_nb_dead);
	pthread_mutex_destroy(&rules->mutex_nb_dead);
	pthread_mutex_destroy(&rules->mutex_rfork);
}
