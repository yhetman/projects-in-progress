/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:04:36 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/12/23 17:12:30 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "corewar_error.h"

t_player	*init_player(int id)
{
	t_player *champ;

	if (!(champ = (t_player *)ft_memalloc(sizeof(t_player))))
		terminate(ERR_PLAYER_INIT);
	champ->id = id;
	champ->name = NULL;
	champ->comment = NULL;
	champ->code_size = 0;
	champ->code = NULL;
	champ->cycle_live = 0;
	champ->current_lives_num = 0;
	champ->previous_lives_num = 0;
	champ->next = NULL;
	return (champ);
}

t_cursor	*init_cursor(t_player *champ, int32_t next_op)
{
	t_cursor		*cursor;
	static uint32_t	cursor_id;

	if (!(cursor = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		terminate(ERR_CURSOR_INIT);
	cursor->id = ++cursor_id;
	cursor->carry = false;
	cursor->op_code = 0;
	cursor->cycle_live = 0;
	cursor->wait = 0;
	cursor->next_op = next_op;
	cursor->next = NULL;
	cursor->registers[INDEX(1)] = -(champ->id);
	cursor->champ = champ;
	return (cursor);
}

void		init_arena(t_vm *vm)
{
	int			id;
	uint32_t	next_op;

	id = 1;
	next_op = 0;
	while (id <= vm->amount_of_champs)
	{
		ft_memcpy(&(vm->arena[next_op]),
			vm->champs[INDEX(id)]->code,
			(size_t)(vm->champs[INDEX(id)]->code_size));
		next_op += MEM_SIZE / vm->amount_of_champs;
		id++;
	}
}
