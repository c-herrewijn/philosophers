/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 15:54:44 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/02 13:53:01 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_settings	settings;
	
	if (parse_input(argc, argv, &settings) < 0)
		return (1);
	return(0);
}
