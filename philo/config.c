/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:38 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/11 11:32:52 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char **argv)
{
	int i;
	int j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && j != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int init_mutex(t_const_philo *var)
{
	int i;

	i = 0;
	while (i < var->num_philo)
	{
		pthread_mutex_init(&(var->forks[i]), NULL);
		i++;
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
	if (check_arg(argv))
		return (print_error("Error in params!"));
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