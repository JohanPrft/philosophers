/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:37:35 by jprofit           #+#    #+#             */
/*   Updated: 2023/01/30 13:40:45 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	long	res;
	long	sign;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (sign * res);
}

time_t	get_time_ms(void)
{
	t_tval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long long	get_time_since_ms(long long start_time)
{
	return (get_time_ms() - start_time);
}

void	usleep_better(time_t usec)
{
	long long	timestamp;

	timestamp = get_time_ms() + usec;
	while (get_time_ms() < timestamp)
		usleep(100);
}

void	clean(t_env *env)
{
	free (env->mutex_tab_fork);
	free (env->philo);
}
//	int i;
//	pthread_mutex_destroy(&env->mutex_print);
//	while (i < env->nb_philo)
//		if (pthread_mutex_destroy(&env->mutex_tab_fork[i]))
//			return (write_error())
