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
    philo->last_meal = rules->start_time_ms;
	if (philo->index % 2)
		usleep_better(10);
	while (rules->nb_dead == 0 && rules->all_ate_enough == 0)
	{
		check_dead(rules, philo);
		action_and_print(rules, philo, "is sleeping");
		usleep_better(rules->time_to_sleep);
//		check_eat(rules, philo);
//		action_and_print(rules, philo, "is thinking", rules->time_to_sleep);
//		action_and_print(rules, philo, "is sleeping", rules->time_to_sleep);
//		 if eat max times
//		 think
	}
	printf("%lld %i died\n", get_time_ms() - rules->start_time_ms, philo->index);
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
		if (pthread_create(&(philo[i].thread_id), NULL, &routine, (void *)&(philo[i])))
			return (0);

	}
	// death
	exit_threads(rules, philo);
	return (1);
}
