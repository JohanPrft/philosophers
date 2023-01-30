/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:19 by jprofit           #+#    #+#             */
/*   Updated: 2023/01/30 18:59:33 by jprofit          ###   ########.fr       */
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

int	fill_struct(int argc, char **argv, t_rules *param)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!check_only_int(argv[i]))
			return (0);
	param->nb_philo = ft_atoi(argv[1]);
	if (param->nb_philo < 1)
		return (0);
	param->time_to_die = ft_atoi(argv[2]);
	if (param->time_to_die < 1)
		return (0);
	param->time_to_eat = ft_atoi(argv[3]);
	if (param->time_to_eat < 1)
		return (0);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (param->time_to_sleep < 1)
		return (0);
	return (1);
}

int	init_philo(t_rules *rules, t_philo *philo)
{
	int	i;

	philo = malloc(sizeof(t_philo) * (rules->nb_philo));
	if (!philo)
		return (0);
	i = 0;
	while (++i <= rules->nb_philo)
	{
		philo[i].index = i;
		printf("%i", philo[i].index);
	}
	return (1);
}

	// int	i;

	// 	pthread_create(, &table[i]);
	// }
