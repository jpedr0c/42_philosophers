/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:03:42 by jocardos          #+#    #+#             */
/*   Updated: 2022/12/22 16:42:08 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

struct s_const_philo;

typedef struct s_philo
{
	int				id;
	int				ate;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	pthread_t		thread_id;
	struct s_const_philo	*var;
}					t_philo;

typedef struct s_const_philo
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				total_ate;
	int				dieded;
	long long		first_time;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	t_philo			philo[250];
}					t_const_philo;


// UTILS
int					ft_atoi(const char *str);
long long			get_time_in_ms(void);
long long			time_diff(long long pres, long long past);
void 				smart_sleep(long long time, t_const_philo *var);
void 				print_action(t_const_philo *var, int id, char *string);

// CONFIG
int	print_error(char *str);
int manager_error(int error);
int init_mutex(t_const_philo *var);
int init_philosophers(t_const_philo *var);
int init_all(t_const_philo *var, char **argv);

// ROUTINE
void philo_eats(t_philo *philo);
void *routine_of_philo(void *void_philo);
void exit_routine(t_const_philo *var, t_philo *philo);
void death_checker(t_const_philo *var, t_philo *philo);
int create_routine(t_const_philo *var);

#endif