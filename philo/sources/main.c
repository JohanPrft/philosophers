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


int	main(int argc, char **argv)
{
	t_rules	rules;
	t_philo	philo;

	if (argc < 5 || argc > 6)
		return (write_error());
	if (!fill_struct(argc, argv, &rules))
		return (write_error());
	if (!init_philo(&rules, &philo))
		return (1);
	return (0);
}
