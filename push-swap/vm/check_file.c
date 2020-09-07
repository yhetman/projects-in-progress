/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 03:12:35 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/26 03:42:05 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void	check_file(int *ac, char ***av, t_vm *vm, t_champion **champs)
{
	long	id;

	id = 0;
	if (*ac >= 3 && !ft_strcmp(**av, "-n"))
	{
		if (!IS_INT(*(*av + 1))
		|| (id = ft_atoi(*(*av + 1))) < 1
		|| id > MAX_PLAYERS
		|| find_player(*champs, id)
		|| !is_cor(*(*av + 2)))
			usage();
		add_player(champs, parse_champion(*(*av + 2), id));
		vm->amount_of_champs++;
		(*ac) -= 3;
		(*av) += 3;
	}
	else if (is_cor(**argv))
	{
		add_player(champs, parse_champion(**av, id));
		vm->amount_of_champs++;
		(*ac)--;
		(*av)++;
	}
	else
		usage();
	}
