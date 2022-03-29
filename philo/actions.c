/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabtaim <ylabtaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:09:37 by ylabtaim          #+#    #+#             */
/*   Updated: 2022/03/26 22:57:10 by ylabtaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *ph)
{
	if (*(ph->alive) == true)
		printer(ph, SLEEPING);
	if (ft_sleep(ph->param->time_to_sleep, ph))
		return (1);
	return (0);
}

int	eating(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	if (*(ph->alive) == true)
		printer(ph, TAKEN_FORK);
	pthread_mutex_lock(ph->right_fork);
	if (*(ph->alive) == true)
		printer(ph, TAKEN_FORK);
	if (*(ph->alive) == true)
		printer(ph, EATING);
	if (ft_sleep(ph->param->time_to_eat, ph))
	{
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		return (1);
	}
	ph->last_meal = get_time() - ph->param->start_time;
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
	ph->meals_eaten++;
	return (0);
}

int	thinking(t_philo *ph)
{
	if (*(ph->alive) == true)
		printer(ph, THINKING);
	if (ph->meals_eaten == 0)
	{
		if (ft_sleep(100, ph))
			return (1);
	}
	return (0);
}

void	*actions(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo == NULL || philo->param->philos_nbr == 1)
		return (NULL);
	if (philo->id % 2 == 1)
		thinking(philo);
	while (1)
	{
		if (eating(philo))
			break ;
		if (philo->meals_eaten == philo->param->meals_to_eat)
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}
