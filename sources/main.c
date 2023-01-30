/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:42:33 by jprofit           #+#    #+#             */
/*   Updated: 2023/01/30 11:58:58 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv)
{
	if (argc == 4)
		philo(argc, argv);
	else
		printf("Please start the porgram with the correct syntax : \n\
./philo <nb_philo> <time_to_die> <time_to_eat> <time_to_sleep>\n");
}
