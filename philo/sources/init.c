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

int	write_error(void)
{
	printf("Please start the program with the correct syntax : \n./philo\
 <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> (<max_nb_eat>)\n");
	return (1);
}

int	check_only_int(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int fill_env(char **argv, int argc, t_env *env)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!check_only_int(argv[i]))
			return (0);
	env->nb_philo = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (env->nb_philo < 1 || env->nb_philo > 200 || env->time_to_die < 0 \
 || env->time_to_eat < 0 || env->time_to_sleep < 0)
		return (0);
	if (argc == 6)
	{
		env->max_meal = ft_atoi(argv[5]);
		if (env->max_meal < 0)
			return (0);
	}
	else
		env->max_meal = -1;
	env->nb_dead = 0;
	env->mutex_tab_fork = malloc(sizeof(pthread_mutex_t) * env->nb_philo);
	if (mutex_init(env) != 1)
		return (0);
	env->ate_enough = 0;
	env->all_ate_enough = 0;
	return (1);
}

int	init_philo(t_env *env, t_philo **philo)
{
	int i;

	*philo = malloc(sizeof(**philo) * env->nb_philo);
	if (!*philo)
		return (0);
	i = -1;
	while (++i < env->nb_philo)
	{
		(*philo)[i].index = i + 1;
		(*philo)[i].env = env;
		(*philo)[i].right_fork_id = i;
		(*philo)[i].left_fork_id = (i + 1) % env->nb_philo;
		(*philo)[i].last_meal = -1;
	}
	return (1);
}
