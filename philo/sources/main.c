/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:42:33 by jprofit           #+#    #+#             */
/*   Updated: 2023/01/30 18:54:44 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	start_simulation(t_env *env, t_philo *philo)
{
	int i;

	env->start_time_ms = get_time_ms() + 1000;
	i = -1;
	while (++i < env->nb_philo)
	{
		if (pthread_create(&philo[i].thread_id, NULL, &philosopher, &(philo[i])))
			return (ERROR);
	}
	hitman(env);
	return (SUCCESS);
}
int	end_simulation(t_env *env, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < env->nb_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL))
			return (ERROR);
	}
	return (SUCCESS);
}

// philo pointer is needed to be an array
int	main(int argc, char **argv)
{
	t_env	env;
	t_philo	*philo;

	if (parsing(argv, argc, &env))
		return (write_error(STR_ERR_SYNTAX, &env));
	if (init_philo(&env, &philo))
		return (ERROR);
	if (start_simulation(&env, philo))
		return (ERROR);
	if (end_simulation(&env, philo))
		return (ERROR);
	clean(&env);
	return (SUCCESS);
}
