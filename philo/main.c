/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:16:22 by jocardos          #+#    #+#             */
/*   Updated: 2022/12/08 19:16:22 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print(t_philo *philo, unsigned long time, char *is_doing)
{
  pthread_mutex_lock(philo->print);
  printf("%lums  %d %s\n", time, philo->id, is_doing);
  pthread_mutex_unlock(philo->print);
}

void *routine_of_philo(void *p)
{
  t_philo *philo;

  philo = (t_philo *)p;
  if (philo->id % 2 == 0)
    usleep(10);
  philo->last_meal = current_time_in_ms();
  while (42)
  {
    pthread_mutex_lock(&philo->mutex[philo->id - 1]);
    print(philo, real_time(philo), "has taken a fork");
    pthread_mutex_lock(&philo->mutex[philo->id % philo->num_philo]);
    print(philo, real_time(philo), "has taken a fork");
    print(philo, real_time(philo), "is eating");
    philo->ate++;
    if (philo->ate == philo->must_eat)
      philo->total_ate++;
    usleep(philo->time_eat * 1000);
    philo->last_meal = current_time_in_ms();
    pthread_mutex_unlock(&philo->mutex[philo->id - 1]);
    pthread_mutex_unlock(&philo->mutex[philo->id % philo->num_philo]);
    print(philo, real_time(philo), "is sleeping");
    usleep(philo->time_eat * 1000);
    print(philo, real_time(philo), "is thinking");
  }
  return (0);
}

void check_all_philo_ate(t_philo *philo)
{
  int i;

  i = 0;
  while (42)
  {
    if (philo[i].total_ate == philo[i].num_philo)
    {
      destroy_mutex(philo);
      free_params(philo, philo->mutex);
      return ;
    }
    if (current_time_in_ms() - philo[i].last_meal > (unsigned long)philo->time_die)
    {
      usleep(100);
      pthread_mutex_lock(philo->print);
      printf("%lums  %d died\n", real_time(philo), philo->id);
      destroy_mutex(philo);
      free_params(philo, philo->mutex);
      return ;
    }
    i = (i + 1) % philo->num_philo;
    usleep(500);
  }
}

int main(int argc, char **argv)
{
  int i;
  t_philo *philo;
  t_philo *memory;
  pthread_t *th;

  if (argc < 5 || argc < 6)
    return (error());
  memory = (t_philo *)malloc(sizeof(t_philo) * philo->num_philo);
  if (config_params(philo, argv))
    return (free_params(0, philo));
  if (init_params(philo))
    return (1);
  th = (pthread_t *)malloc(sizeof(pthread_t) * philo->num_philo);
  i = -1;
  while (++i < philo->num_philo)
  {
    pthread_create(&th[i], NULL, routine_of_philo, philo + i);
    usleep(100);
  }
  check_all_philo_ate(philo);
  free(th);
  return (0);
}
