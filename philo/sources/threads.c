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
	t_rules	*rules;

	philo = (t_philo *)void_philo;
	rules = philo->param;
    philo->last_meal = get_time_ms();
	while (rules->nb_dead == 0 && rules->all_ate_enough == 0)
	{
		check_dead(rules, philo);
		action_and_print(rules, philo->index, "is sleeping", rules->time_to_sleep);
//		 if eat max times
//		 sleep if have eat
//		 think
	}
	return (NULL);
}

void exit_threads(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philo[i].thread_id, NULL);
}

int	create_threads(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	rules->start_time_ms = get_time_ms();
	while (++i < rules->nb_philo)
	{
		//printf ("left fork id   %i\n", philo[i].left_fork_id);
		//printf ("right fork id  %i\n", philo[i].right_fork_id);
		if (pthread_create(&(philo[i].thread_id), NULL, &routine, (void *)&(philo[i])))
			return (0);

	}
	// death
	exit_threads(rules, philo);
	return (1);
}
