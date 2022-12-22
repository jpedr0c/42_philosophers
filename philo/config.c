/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:38 by jocardos          #+#    #+#             */
/*   Updated: 2022/12/22 16:11:06 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str)
{
	printf("\e[31mError: \e[0m");
	printf("\e[31m%s\e[0m\n", str);
	printf("\e[31mPlease enter: num_philo time_die time_eat time_sleep\e[0m\n");
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

int init_mutex(t_const_philo *var)
{
	int i;

	i = var->num_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(var->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(var->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(var->meal_check), NULL))
		return (1);
	return (0);
}

int init_philosophers(t_const_philo *var)
{
	int i;

	i = var->num_philo;
	while (--i >= 0)
	{
		var->philo[i].id = i;
		var->philo[i].ate = 0;
		var->philo[i].left_fork = i;
		var->philo[i].right_fork = (i + 1) % var->num_philo;
		var->philo[i].last_meal = 0;
		var->philo[i].var = var;
	}
	return (0);
}

int init_all(t_const_philo *var, char **argv)
{
	var->num_philo = ft_atoi(argv[1]);
	var->time_die = ft_atoi(argv[2]);
	var->time_eat = ft_atoi(argv[3]);
	var->time_sleep = ft_atoi(argv[4]);
	var->total_ate = 0;
	var->dieded = 0;
	if (var->num_philo < 1 || var->time_die < 60 || var->time_eat < 60 || var->time_sleep < 60 || var->num_philo > 200)
		return (1);
	if (argv[5])
	{
		var->nb_eat = ft_atoi(argv[5]);
		if (var->nb_eat <= 0)
			return (1);
	}
	else
		var->nb_eat = -1;
	if (init_mutex(var))
		return (2);
	init_philosophers(var);
	return (0);
}