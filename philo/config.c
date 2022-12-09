/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:38 by jocardos          #+#    #+#             */
/*   Updated: 2022/12/08 16:05:38 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(char **argv)
{
  int i;
  int j;

  i = 1;
  j = 0;
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

int config_params(t_philo *philo, char **argv)
{
  if (check_args(argv))
    return (error());
  philo->total_ate = 0;
  philo->time = current_time_in_ms();
  philo->num_philo = ft_atoi(argv[1]);
  philo->time_die = ft_atoi(argv[2]);
  philo->time_eat = ft_atoi(argv[3]);
  philo->time_sleep = ft_atoi(argv[4]);
  if (philo->num_philo <= 0 || philo->time_die <= 0 || philo->time_eat <= 0 || philo->time_sleep <= 0)
    return (1);
  if (argv[5])
  {
    philo->must_eat = ft_atoi(argv[5]);
    if (philo->must_eat <= 0)
      return (1);
  }
  else
    philo->must_eat = -1;
  return (0); 
}

void assign_params(t_philo *philo, pthread_mutex_t *m, pthread_mutex_t *pr)
{
  int i;

  i = 0;
  while (i < philo->num_philo)
  {
    philo[i].ate = 0;
    philo[i].id = i + 1;
    philo[i].mutex = m;
    philo[i].print = pr;
    i++;
  }
}

int free_params(t_philo *philo, pthread_mutex_t *m)
{
  if (philo)
    free(philo);
  if (m)
    free(m);
  return (1);
}

int init_params(t_philo *philo)
{
  pthread_mutex_t *m;
  pthread_mutex_t pr;
  int i;

  i = 0;
  m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->num_philo);
  if (!m || !philo)
    return (free_params(philo, m));
  while (i < philo->num_philo)
    if (pthread_mutex_init(&m[i++], 0))
      return (free_params(philo, m));
    if (pthread_mutex_init(&pr, 0))
      return (free_params(philo, m));
    assign_params(philo, m, &pr);
    return (0);
}