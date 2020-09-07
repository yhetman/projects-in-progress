/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:14:30 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/12/16 16:20:20 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	add_cursor(t_cursor **list, t_cursor *new)
{
	if (new)
		new->next = *list;
	*list = new;
}

void	set_cursors(t_vm *vm)
{
	int32_t		id;
	uint32_t	next_op;

	id = 1;
	next_op = 0;
	while (id <= vm->amount_of_champs)
	{
		add_cursor(&(vm->cursors), init_cursor(vm->champs[INDEX(id)], next_op));
		vm->amount_of_cursors++;
		next_op += MEM_SIZE / vm->amount_of_champs;
		id++;
	}
}
