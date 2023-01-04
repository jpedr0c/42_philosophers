/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:49:31 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/04 17:45:31 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			signal;
	long int	result;
	size_t		i;

	i = 0;
	signal = 1;
	result = 0;
	while (str[i] && (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			signal = -1;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return ((int)(result * signal));
}

long long	get_time_in_ms(struct timeval time)
{
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + time.tv_usec / 1000);
}

long long	time_diff(long long pres, long long past)
{
	return (pres - past);
}

// void smart_sleep(long long time, t_const_philo *var)
// {
// 	long long start;

// 	start = get_time_in_ms();
// 	while (!(var->dieded))
// 	{
// 		if (time_diff(get_time_in_ms(), start) >= time)
// 			break ;
// 		usleep(50);
// 	}
// }

void smart_sleep(long long time, t_const_philo *var)
{
	long long start;
	long long before;
	struct timeval time_before;
	struct timeval time_now;

	before = get_time_in_ms(time_before);
	while (!(var->dieded))
	{
		start = get_time_in_ms(time_now);
		if (time_diff(start, before) >= time)
			break ;
		usleep(50);
	}
}

void print_action(t_const_philo *var, int id, char *string)
{
	struct timeval time_now;

	pthread_mutex_lock(&(var->writing));
	if (!(var->dieded))
	{
		printf("%llims ", get_time_in_ms(time_now) - var->first_time);
		printf("%i ", id + 1);
		printf("%s\n ", string);
	}
	pthread_mutex_unlock(&(var->writing));
	return ;
}