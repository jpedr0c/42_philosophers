/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:42:08 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/04 17:07:16 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_eats(t_philo *philo)
{
    t_const_philo *var;
    struct timeval time_now;

    var = philo->var;
    pthread_mutex_lock(&(var->forks[philo->left_fork]));
    print_action(var, philo->id, "has taken a fork");
    pthread_mutex_lock(&(var->forks[philo->right_fork]));
    print_action(var, philo->id, "has taken a fork");
    pthread_mutex_lock(&(var->meal_check));
    philo->last_meal = get_time_in_ms(time_now);
    print_action(var, philo->id, "is eating");
    pthread_mutex_unlock(&(var->meal_check));
    smart_sleep(var->time_eat, var);
    (philo->ate)++;
    pthread_mutex_unlock(&(var->forks[philo->left_fork]));
    pthread_mutex_unlock(&(var->forks[philo->right_fork]));
}

void *routine_of_philo(void *void_philo)
{
    int i;
    t_philo *philo;
    t_const_philo *var;

    i = 0;
    philo = (t_philo *)void_philo;
    var = philo->var;
    if (philo->id % 2 == 0)
        usleep(philo->var->time_eat * 1000);
    while (!(var->dieded))
    {
        philo_eats(philo);
        if (var->total_ate)
            break ;
        print_action(var, philo->id, "is sleeping");
        smart_sleep(var->time_sleep, var);
        print_action(var, philo->id, "is thinking");
        i++;
    }
    return (NULL);
}

void exit_routine(t_const_philo *var, t_philo *philo)
{
    int i;

    i = 0;
    while (i < var->num_philo)
    {
        pthread_join(philo[i].thread_id, NULL);
        i++;
    }
    i = 0;
    while (i < var->num_philo)
    {
        pthread_mutex_destroy(&(var->forks[i]));
        i++;
    }
	pthread_mutex_destroy(&var->meal_check);
    pthread_mutex_destroy(&(var->writing));
}

void death_checker(t_const_philo *var, t_philo *philo)
{
     int i;
     struct timeval time_now;

     while(!(var->total_ate))
     {
        i = -1;
        while (++i < var->num_philo && !(var->dieded))
        {
            pthread_mutex_lock(&(var->meal_check));
            if (time_diff(get_time_in_ms(time_now), philo[i].last_meal) > var->time_die)
            {
                usleep(100);
                print_action(var, i, "died");
                var->dieded = 1;
            }
            pthread_mutex_unlock(&(var->meal_check));
        }
        if (var->dieded)
            break ;
        i = 0;
        while(var->nb_eat != -1 && i < var->num_philo && philo[i].ate >= var->nb_eat)
            i++;
        if (i == var->num_philo)
            var->total_ate = 1;
        usleep(500);
     }
}

int create_routine(t_const_philo *var)
{
    int i;
    t_philo *philo;
    struct timeval time_now;

    i = 0;
    philo = var->philo;
    var->first_time = get_time_in_ms(time_now);
    while (i < var->num_philo)
    {
        if (pthread_create(&(philo[i].thread_id), NULL, routine_of_philo, &(philo[i])))
            return (1);
        philo[i].last_meal = get_time_in_ms(time_now);
        i++;
    }
    death_checker(var, var->philo);
    exit_routine(var, philo);
    return (0);
}