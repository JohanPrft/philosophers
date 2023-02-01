/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idk.c             	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johan <johan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:19 by jprofit           #+#    #+#             */
/*   Updated: 2023/01/31 11:07:20 by johan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *void_philo)
{
	t_philo *philo;
	t_rules	*rules;

	philo = (t_philo *)void_philo;
	rules = philo->param;
//	while (philo->state != DEAD)
//	{
		// eat;
		// if eat max times
		// sleep if have eat
		// think
//	}
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
	while (++i < rules->nb_philo)
	{
		printf ("left fork id %i\n", philo[i].left_fork_id);
		if (pthread_create(&(philo[i].thread_id), NULL, &routine, (void *)&(philo[i])))
			return (0);
	}
	// death
	exit_threads(rules, philo);
	return (1);
}