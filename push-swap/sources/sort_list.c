/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 02:37:17 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/19 18:32:38 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ps.h"

static void	swap_pointers(t_ilst **first, t_ilst **second)
{
	t_ilst	*swap;

	swap = NULL;
	if (!*second || !*first)
		return ;
	swap = (*second)->next;
	(*second)->next = *first;
	*first = *second;
	*second = swap;
}

static int	check_throught_list(t_ilst *list)
{
	if (!list)
		return (0);
	while (list->next && list->x < list->next->x)
		list = list->next;
	return ((!list->next) ? 1  : 0);
}

char		*sort_list(t_ilst **first, int i)
{
	t_ilst	*second;
	char	*str;

	str = NULL;
	second = NULL;
	ft_bzero(second, sizeof(t_ilst));
	while (!check_throught_list(*first) || second)
	{
		i = run_throught_first(first, *first, &str);
		run_throught_second(&second, second, &str);
		if (!i)
		{
			swap_pointers(&second, first);
			str = ft_strjoin(str, "pb");
		}
		if (check_throught_list(*first) && second)
		{
			swap_pointers(first, &second);
			str = ft_strjoin(str, "pa");
		}
	}
	return (str);
}


