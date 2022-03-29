/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:38:54 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/03/26 21:11:20 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (printf("Error: Wrong Syntax\n"), 1);
	while (av[i])
	{
		j = 0;
		if (ft_atoi(av[i]) <= 0)
			return (printf("Error: Unvalid arguments\n"), 1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (printf("Error: Unvalid arguments\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

void	stock_args(t_param *param, int ac, char **av)
{
	param->start_time = get_time();
	param->philos_nbr = ft_atoi(av[1]);
	param->time_to_die = ft_atoi(av[2]);
	param->time_to_eat = ft_atoi(av[3]);
	param->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		param->meals_to_eat = ft_atoi(av[5]);
	else
		param->meals_to_eat = -1;
}

int	main(int ac, char **av)
{
	t_param	param;
	t_philo	*philo;

	if (check_args(ac, av))
		return (1);
	stock_args(&param, ac, av);
	philo = create_philo(&param);
	if (philo == NULL && free_data(philo) == 0)
		return (1);
	if (param.philos_nbr == 1)
	{
		printer(philo, TAKEN_FORK);
		ft_sleep(param.time_to_die, philo);
		printer(philo, DEAD);
	}
	if (join_philo(philo, param.philos_nbr) && free_data(philo) == 0)
		return (1);
	free_data(philo);
	return (0);
}
