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

int	check_dead(t_env *env, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < env->nb_philo)
	{
		// need mutex on the time of the last meal
		if (get_time_ms() - philo[i].last_meal >= env->time_to_die)
		{
			print_action(env, &philo[i], DIED);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	check_all_eat(t_env *env, t_philo *philo)
{
	int	i;
	int nb_eat_enough;

	if (env->max_meal == -1)
		return (0);
	i = -1;
	nb_eat_enough = 0;
	while (++i < env->nb_philo)
	{
		// need mutex on the nb of meal
		if (philo[i].nb_meal >= env->max_meal)
			nb_eat_enough++;
	}
	if (nb_eat_enough == env->nb_philo)
		return (1);
	else
		return (0);
}

void    print_action(t_env *env, t_philo *philo, t_action action)
{
	static char *tab_action[] = {"is eating", "has taken a fork", "is sleeping", "is thinking", "died"};

	pthread_mutex_lock(&env->mutex_print);
	printf("%lld %i %s\n", get_time_ms() - env->start_time_ms, philo->index, tab_action[action]);
	if (action != DIED)
		pthread_mutex_unlock(&env->mutex_print);
}
