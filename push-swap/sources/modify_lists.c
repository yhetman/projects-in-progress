/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 07:18:55 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/19 18:21:17 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ps.h"

static void	reverce_tail(t_ilst **list, char **str, char *add)
{
	t_ilst	*tmp;

	tmp = NULL;
	if (*list && (*list)->next)
	{
		tmp = *list;
		while (tmp->next->next)
			tmp = tmp->next;
		tmp->next->next = *list;
		*list = tmp->next;
		tmp->next = NULL;
		*str = ft_strjoin(*str, add);
	}
}

static void	reverce_head(t_ilst **list, char **str, char *add)
{
	t_ilst	*tmp;
	t_ilst	*hell;

	tmp = NULL;
	hell = NULL;
	if (*list && (*list)->next)
	{
		tmp = *list;
		*list = (*list)->next;
		tmp->next = NULL;
		hell = *list;
		while (hell->next)
			hell = hell->next;
		hell->next = tmp;
		*str = ft_strjoin(*str, add);
	}
}

static int	check_throught_list(t_ilst *list)
{
	if (!list)
		return (0);
	while (list->next && list->x < list->next->x)
		list = list->next;
	return ((!list->next) ? 1 : 0);
}

int		run_throught_first(t_ilst **first, t_ilst *last, char **str)
{
	int i;

	if (last)
		while (last->next)
			last = last->next;
	if ((*first)->x > last->x && (*first)->x < (*first)->next->x)
	{
		reverce_tail(first, str, "rra ");
		run_throught_first(first, *first, str);
	}
	if ((*first)->x > last->x)
	{
		reverce_head(first, str, "ra ");
		run_throught_first(first, *first, str);
	}
	if ((*first)->x > (*first)->next->x)
	{
		i = (*first)->x;
		(*first)->x = (*first)->next->x;
		(*first)->next->x = i;
		*str = ft_strjoin(*str, "sa ");
	}
	return (check_throught_list(*first));
}

void	run_throught_second(t_ilst **second, t_ilst *last, char **str)
{
	int	i;

	if (last)
		while (last->next)
			last = last->next;
	if ((*second) && (*second)->next)
	{
		if (last->x > (*second)->x && (*second)->x > (*second)->next->x)
		{
			reverce_tail(second, str, "rrb ");
			run_throught_second(second, *second, str);
		}
		if ((*second)->x < last->x)
		{
			reverce_head(second, str, "rb ");
			run_throught_second(second, *second, str);
		}
		if ((*second)->x < (*second)->next->x)
		{
			i = (*second)->x;
			(*second)->x = (*second)->next->x;
			(*second)->next->x = i;
			*str = ft_strjoin(*str, "sb ");
		}
	}
}
