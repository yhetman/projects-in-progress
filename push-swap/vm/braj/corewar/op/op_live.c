/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 20:23:16 by ablizniu          #+#    #+#             */
/*   Updated: 2018/12/24 23:09:21 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "corewar_op.h"
#include "corewar_vs.h"

inline static void	log_live(uint32_t cursor_id, int32_t player_id)
{
	ft_printf("P %4d | live %d\n", cursor_id, player_id);
}

inline static void	log_live_msg(int32_t player_id, char *player_name)
{
	ft_printf("Player %d (%s) is said to be alive\n",
													player_id,
													player_name);
}

void				op_live(t_vm *vm, t_cursor *cursor)
{
	int32_t		player_id;
	t_player	*champ;

	cursor->step += OP_CODE_LEN;
	player_id = get_op_arg(vm, cursor, 1, false);
	vm->lives++;
	cursor->cycle_live = vm->cycles;
	champ = NULL;
	if (player_id <= -1 && player_id >= -((int32_t)vm->amount_of_champs))
	{
		champ = vm->champs[INDEX(FT_ABS(player_id))];
		champ->cycle_live = vm->cycles;
		champ->current_lives_num++;
		vm->alive = champ;
		if (vm->vs)
		{
			vm->vs->map[cursor->next_op].wait_cycles_live = CYCLE_TO_WAIT;
			vm->vs->map[cursor->next_op].player_live = champ;
		}
	}
	if (vm->log & OP_LOG)
		log_live(cursor->id, player_id);
	if (vm->log & LIVE_LOG && champ)
		log_live_msg(FT_ABS(player_id), champ->name);
}
