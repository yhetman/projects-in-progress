/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 02:52:25 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/19 18:39:31 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ps.h"

static t_ilst	*initialize_list(char **argv)
{
	t_ilst		*temp;
	t_ilst		*list;

	if (!(temp = (t_ilst*)malloc(sizeof(t_ilst))))
		return (NULL);
	ft_bzero((void*)temp, sizeof(t_ilst));
	list = temp;
	while (++argv)
	{
		temp->x = ft_atoi(*argv);
		if (argv + 1)
		{
			if (!(temp->next = (t_ilst*)malloc(sizeof(t_ilst))))
				return (NULL);
			ft_bzero((void*)temp->next, sizeof(t_ilst));
			temp = temp->next;
		}
	}
	return (list);
}

static bool		no_equals(t_ilst *list, t_ilst *temp)
{
	while (list->next)
	{
		temp = list->next;
		while (temp)
		{
			if (temp->x == list->x)
				return (false);
			temp = temp->next;
		}
		list = list->next;
	}
	return (true);
}

static int		emergency_exit(t_ilst **list, char *str, int fd, int exit_code)
{
	t_ilst		*tmp;

	ft_putstr_fd(str, fd);
	if (!list || !*list)
		exit(exit_code);
	while (*list)
	{
		tmp = (*list)->next;
		(*list)->x = 0;
		free(*list);
		*list = tmp;
	}
	tmp = NULL;
	*list = NULL;
	exit(exit_code);
}

static bool		checker(int argc, char **argv)
{
	int			i;

	while (--argc)
	{
		i = -1;
		while (argv[argc][++i])
			if (argv[argc][0] != '-' || !(IS_DIGIT(argv[argc][i])))
				return (false);
		if (ft_strlen(argv[argc]) >= 10)
		{
			if (ft_strcmp("2147483647", argv[argc]) > 0)
				return (false);
			if (ft_strcmp("-2147483648", argv[argc]) > 0)
				return (false);
		}
	}
	return (true);
}

int				main(int argc, char **argv)
{
	t_ilst		*list;

	if (argc == 1)
		ft_putstr_fd("Usage: ./push_swap {val1} {val2} ...", 1);
	if (argc > 2)
	{
		if (!checker(argc, argv))
			emergency_exit(&list, "ERROR\n", STD_ERR, FAIL);
		list = initialize_list(argv);
		if (!no_equals(list, list->next))
			emergency_exit(&list, "ERROR\n", STD_ERR, FAIL);
		ft_printf("Sorted stack : %s\n", sort_list(&list, 0));
	}
	return (0);
}
