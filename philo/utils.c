/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:49:31 by jocardos          #+#    #+#             */
/*   Updated: 2022/12/08 15:49:31 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int error(void)
{
	printf("\e[31mError!!!\e[0m\n");
	printf("\e[31mPlease enter: num_philo time_die time_eat time_sleep\e[0m\n");
	return (1);
}

int ft_atoi(char *str)
{
  int		signal;
	long	result;
	size_t	i;

	i = 0;
	signal = 1;
	result = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			||str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
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
	return (result * signal);
}

void  destroy_mutex(t_philo *philo)
{
  int i;

  i = 0
  while (i < philo->num_philo)
    pthread_mutex_destroy(&philo->mutex[i++]);
}

unsigned long current_time_in_ms(void)
{
  struct timeval time;
  unsigned long l;
  unsigned long s;
  unsigned long u;

  gettimeofday(&time, NULL);
  s = (time.tv_sec * 1000);
  u = (time.tv_usec / 1000);
  l = s + u;
  return (l);
}

unsigned long real_time(t_philo *philo)
{
  return (current_time_in_ms() - philo->time);
}