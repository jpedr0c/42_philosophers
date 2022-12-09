/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:03:42 by jocardos          #+#    #+#             */
/*   Updated: 2022/12/01 21:03:42 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
  int num_philo;
  int time_die;
  int time_eat;
  int time_sleep;
  int must_eat;
  int total_ate;
  unsigned long time;
  int ate;
  int id;
  pthread_mutex_t *mutex;
  pthread_mutex_t *print;
  unsigned long last_meal;
}t_philo;


// UTILS
int error(void);
int ft_atoi(char *str);
void  destroy_mutex(t_philo *philo);
unsigned long current_time_in_ms(void);
unsigned long real_time(t_philo *philo);

// CONFIG
int check_args(char **argv);
int config_params(t_philo *philo, char **argv);
void assign_params(t_philo *philo, pthread_mutex_t *m, pthread_mutex_t *pr);
int free_params(t_philo *philo, pthread_mutex_t *m);
int init_params(t_philo *philo);

// MAIN
void print(t_philo *philo, unsigned long time, char *is_doing);
void *routine_of_philo(void *p);
void check_all_philo_ate(t_philo *philo);

#endif