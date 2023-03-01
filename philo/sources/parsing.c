/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:26:44 by jprofit           #+#    #+#             */
/*   Updated: 2023/02/23 18:26:44 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int parsing(char **argv, int argc, t_env *env)
{
	int	i;

	env->mutex_tab_fork = NULL;
	env->philo = NULL;
	if (argc < 5 || argc > 6)
		return (ERROR);
	i = 0;
	while (++i < argc)
		if (!check_only_int(argv[i]))
			return (ERROR);
	env->nb_philo = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (env->nb_philo < 1 || env->nb_philo > 200 || env->time_to_die < 0 \
 || env->time_to_eat < 0 || env->time_to_sleep < 0)
		return (ERROR);
	if (argc == 6)
	{
		env->max_meal = ft_atoi(argv[5]);
		if (env->max_meal < 0)
			return (ERROR);
	}
	else
		env->max_meal = -1;
	env->stop_simulation = false;
	return (SUCCESS);
}
