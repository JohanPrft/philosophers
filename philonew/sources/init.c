/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:19 by jprofit           #+#    #+#             */
/*   Updated: 2023/02/06 10:50:11 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	write_error(char *str, t_env *env)
{
	free (env->philo);
	fprintf(stderr, "%s\n", str);
	return (0);
}

int mutex_init(t_env *env) {
	if (pthread_mutex_init(&env->mutex_print, 0))
		return (0);
	return (1);
}

/*
 * init_philo:
 * create and allocate an array of philosopher with all infos
 * due to subject first philo has an index (philo.index) of 1
 */
int	init_philo(t_env *env, t_philo **philo)
{
	int i;
	int subject_i;

	*philo = malloc(sizeof(**philo) * env->nb_philo);
	if (!*philo)
		return (0);
	i = -1;
	while (++i < env->nb_philo)
	{
		subject_i = i + 1;
		(*philo)[i].index = subject_i;
		(*philo)[i].env = env;
		(*philo)[i].right_fork_id = subject_i;
		(*philo)[i].left_fork_id = (subject_i + 1) % env->nb_philo;
		(*philo)[i].last_meal = -1;
		//printf ("philo %i : right_fork_id %i, left_fork_id %i\n", (*philo)[i].index, (*philo)[i].right_fork_id, (*philo)[i].left_fork_id);
	}
	env->philo = *philo;
	return (1);
}

/*
 * 	env->mutex_tab_fork = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (mutex_init(env) != 1)
	{
		free(philo);
		return (0);
	}
 */