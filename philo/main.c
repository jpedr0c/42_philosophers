/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 19:16:22 by jocardos          #+#    #+#             */
/*   Updated: 2023/01/17 14:50:56 by jocardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_const_philo	var;
	int				init;

	if (argc != 5 && argc != 6)
		return (print_error("Wrong amount of arguments"));
	init = init_all(&var, argv);
	if (init)
		return (manager_error(init));
	if (create_routine(&var))
		return (print_error("There was an error creating the threads"));
	return (0);
}
