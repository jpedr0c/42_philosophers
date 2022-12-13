/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:05:38 by jocardos          #+#    #+#             */
/*   Updated: 2022/12/13 18:21:21 by jocardos         ###   ########.fr       */
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

int config_params(t_const_philo *var, char **argv)
{
  if (check_args(argv))
    return (error());
  var->total_ate = 0;
  var->time = current_time_in_ms();
  var->num_philo = ft_atoi(argv[1]);
  var->time_die = ft_atoi(argv[2]);
  var->time_eat = ft_atoi(argv[3]);
  var->time_sleep = ft_atoi(argv[4]);
  if (var->num_philo <= 0 || var->time_die <= 0 || var->time_eat <= 0 || var->time_sleep <= 0)
    return (1);
  if (argv[5])
  {
    var->must_eat = ft_atoi(argv[5]);
    if (var->must_eat <= 0)
      return (1);
  }
  else
    var->must_eat = -1;
  return (0); 
}

void assign_params(t_philo *philo, t_const_philo *var, pthread_mutex_t *m, pthread_mutex_t *pr)
{
  int i;

  i = 0;
  while (i < var->num_philo)
  {
    philo[i].ate = 0;
    philo[i].id = i + 1;
    philo[i].mutex = m;
    philo[i].print = pr;
    philo[i].var = var;
    i++;
  }
}

int free_params(t_philo *philo, pthread_mutex_t *m, t_const_philo *var)
{
  if (philo)
    free(philo);
  if (m)
    free(m);
  if (var)
    free(var);
  return (1);
}

int init_params(t_philo *philo, t_const_philo *var)
{
  pthread_mutex_t *m;
  pthread_mutex_t pr;
  int i;

  i = 0;
  m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->num_philo);
  if (!m || !philo)
    return (free_params(philo, m, var));
  while (i < var->num_philo)
    if (pthread_mutex_init(&m[i++], 0))
      return (free_params(philo, m, var));
  if (pthread_mutex_init(&pr, 0))
    return (free_params(philo, m, var));
  assign_params(philo, var, m, &pr);
  return (0);
}