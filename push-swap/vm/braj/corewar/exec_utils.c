/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:46:00 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/12/24 14:50:51 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_op.h"
#include "corewar_vs.h"

void	update_op_code(t_vm *vm, t_cursor *current)
{
	current->op_code = vm->arena[current->next_op];
	if (vm->arena[current->next_op] >= 0x01 && vm->arena[current->next_op] <= 0x10)
		current->wait = g_op[INDEX(current->op_code)].cycles;
}

void	move_cursor(t_vm *vm, t_cursor *cursor)
{
	if (vm->vs)
		clear_cursor(vm, cursor);
	cursor->next_op += cursor->step;
	cursor->next_op = calc_addr(cursor->next_op);
	if (vm->vs)
		draw_cursor(vm, cursor);
	cursor->step = 0;
	ft_bzero(cursor->args, 3);
}
