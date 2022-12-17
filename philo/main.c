/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:16:22 by jocardos          #+#    #+#             */
/*   Updated: 2022/12/13 18:52:52 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, unsigned long time, char *is_doing)
{
	pthread_mutex_lock(philo->print);
	printf("%lums  %d %s\n", time, philo->id, is_doing);
	pthread_mutex_unlock(philo->print);
}

void short_sleep(unsigned long time, t_philo *philo)
{
  unsigned long start;
  unsigned long time_diff;
  unsigned long before;
  struct timeval time_before;
  struct timeval time_now;

  gettimeofday(&time_before, NULL);
  time_before = current_time_in_ms();
  before = time_before;
  while (!(philo->var->end))
  {
    gettimeofday(&time_now, NULL);
    time_now = current_time_in_ms();
    start = time_now;
    time_diff = start - before;
    if (time_diff >= time)
      break ;
    usleep(50);
  }
}

void	*routine_of_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(philo->var->time_eat * 1000);
	philo->last_meal = current_time_in_ms();
	while (42)
	{
		pthread_mutex_lock(&philo->mutex[philo->id - 1]);
		print(philo, real_time(philo), "has taken a fork");
		pthread_mutex_lock(&philo->mutex[philo->id % philo->var->num_philo]);
		print(philo, real_time(philo), "has taken a fork");
		print(philo, real_time(philo), "is eating");
		philo->ate++;
		if (philo->ate == philo->var->must_eat)
			philo->var->total_ate++;
    short_sleep(philo->var->time_eat, philo);
		philo->last_meal = current_time_in_ms();
		pthread_mutex_unlock(&philo->mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->id % philo->var->num_philo]);
		print(philo, real_time(philo), "is sleeping");
    short_sleep(philo->var->time_sleep, philo);
		print(philo, real_time(philo), "is thinking");
	}
	return (0);
}

void	check_all_philo_ate(t_philo *philo, t_const_philo *var)
{
	int	i;

	i = 0;
	while (42)
	{
		if (philo[i].var->total_ate == philo[i].var->num_philo)
		{
      philo->var->end = 1;
			destroy_mutex(philo);
			free_params(philo, philo->mutex, var);
			return ;
		}
		if (current_time_in_ms()
			- philo[i].last_meal > (unsigned long)philo->var->time_die)
		{
			usleep(100);
      philo->var->end = 1;
			pthread_mutex_lock(philo->print);
			printf("%lums  %d died\n", real_time(philo), philo->id);
			destroy_mutex(philo);
			free_params(philo, philo->mutex, var);
			return ;
		}
		i = (i + 1) % var->num_philo;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int				i;
	t_philo			*philo;
	t_const_philo	*var;
	pthread_t		*th;

	if (argc != 5 && argc != 6)
		return (error());
	var = (t_const_philo *)malloc(sizeof(t_const_philo));
	if (config_params(var, argv))
		return (free_params(0, 0, var));
	philo = (t_philo *)malloc(sizeof(t_philo) * var->num_philo);
	if (init_params(philo, var))
		return (1);
	th = (pthread_t *)malloc(sizeof(pthread_t) * var->num_philo);
	i = -1;
	while (++i < philo->var->num_philo)
	{
		pthread_create(&th[i], NULL, routine_of_philo, philo + i);
		usleep(100);
	}
	check_all_philo_ate(philo, var);
	free(th);
	return (0);
}
