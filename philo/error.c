/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:44:26 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/04 16:04:34 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str)
{
	printf("\e[31mError: \e[0m");
	printf("\e[31m%s\e[0m\n", str);
	return (1);
}

int manager_error(int error)
{
	if (error == 1)
		return (print_error("At least one wrong argument"));
	if (error == 2)
		return (print_error("Fatal error when initializing mutex"));
	return (1);
}

void destroy_mutex(t_const_philo *var)
{
	int i;

	i = 0;
	while (i < var->num_philo)
	{
		pthread_mutex_destroy(&var->meal_check);
		pthread_mutex_destroy(&var->forks[i++]);

	}
}