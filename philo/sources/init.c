/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johan <johan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:19 by jprofit           #+#    #+#             */
/*   Updated: 2023/01/31 11:07:20 by johan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	write_error(void)
{
	printf("Please start the program with the correct syntax : \n./philo\
 <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep> (<max_nb_eat>)\n");
	return (1);
}

int	check_only_int(char *str)
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

int fill_rules(char **argv, int argc, t_rules *param)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!check_only_int(argv[i]))
			return (0);
	param->nb_philo = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (param->nb_philo < 2 || param->nb_philo > 200 ||param->time_to_die < 0 \
	|| param->time_to_eat < 0 || param->time_to_sleep < 0)
		return (0);
	if (argv[5])
	{
		param->max_meal = ft_atoi(argv[5]);
		if (param->max_meal < 0)
			return (0);
	}
	else
		param->max_meal = -1;
	return (1);
}

int	init_philo(t_rules *rules, t_philo **philo)
{
	int i;

	*philo = malloc(sizeof(**philo) * rules->nb_philo);
	if (!*philo)
		return (0);
	i = -1;
	while (++i < rules->nb_philo)
	{
		(*philo)[i].index = i;
		(*philo)[i].param = rules;
		(*philo)[i].state = INIT;
		(*philo)[i].right_fork_id = i;
		(*philo)[i].left_fork_id = (i + 1) % rules->nb_philo;
		(*philo)[i].last_meal = -1;
	}
	return (1);
}
