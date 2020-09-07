/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:48:59 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/12/23 19:06:22 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "corewar_vs.h"
#include <stdio.h>
#include <errno.h>

void	vm_exit(char *msg, t_vm *vm)
{
	ft_putendl_fd(msg, 1);
	if (vm)
		free_vm(&vm)
	exit(1);
}

void	usage()
{
	ft_putendl_fd("Usage: \n", 1);
	ft_putstr_fd("\t\t{ ./corewar [-dump [nbr_cycles]]", 1);
	ft_putstr_fd(["[-n [number]] champion1.cor] ... }\n", 1);
	exit(SUCCESS);
}

inline int8_t	get_byte(t_vm *vm, int32_t next_op, int32_t step)
{
	return (vm->arena[calc_addr(next_op + step)]);
}
