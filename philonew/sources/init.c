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
	clean(env);
	fprintf(stderr, "%s\n", str);
	return (ERROR);
}

int mutex_init(t_env *env)
{
	int i;

	env->mutex_tab_fork = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	i = -1;
	while (++i < env->nb_philo)
		if (pthread_mutex_init(&env->mutex_tab_fork[i], 0))
			return (ERROR);
	if (pthread_mutex_init(&env->mutex_stop_simu, 0))
		return (ERROR);
	if (pthread_mutex_init(&env->mutex_print, 0))
		return (ERROR);
	return (SUCCESS);
}

/*
 * assigning forks for each philo is different half the time
 * otherwise it can lead to deadlock :
 * a philo lock a mutex for the first fork, then wait for the second one
 * who had been taken by a second philo waiting for the first one
 */
void	assign_forks(t_env *env, t_philo *philo, int i_philo)
{
	if (i_philo % 2 == 1)
	{
		philo->right_fork_id = i_philo;
		philo->left_fork_id = (i_philo % env->nb_philo) + 1;
	}
	else
	{
		philo->right_fork_id = (i_philo % env->nb_philo) + 1;
		philo->left_fork_id = i_philo;
	}
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
		return (write_error(STR_ERR_MALLOC, env));
	i = -1;
	while (++i < env->nb_philo)
	{
		subject_i = i + 1;
		(*philo)[i].index = subject_i;
		(*philo)[i].env = env;
		assign_forks(env, &(*philo)[i], subject_i);
		(*philo)[i].last_meal = -1;
		if (pthread_mutex_init(&(*philo)[i].mutex_meal, 0))
			return (write_error(STR_ERR_MUTEX, env));
		printf("philo n%i, %i, %i\n", (*philo)[i].index, (*philo)[i].left_fork_id, (*philo)[i].right_fork_id);
	}
	env->philo = *philo;
	if (mutex_init(env))
		return (write_error(STR_ERR_MUTEX, env));
	return (SUCCESS);
}

/*
 * 	env->mutex_tab_fork = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (mutex_init(env) != 1)
	{
		free(philo);
		return (0);
	}
 */