/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:49:45 by ablizniu          #+#    #+#             */
/*   Updated: 2018/11/30 20:53:17 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "corewar_op.h"

inline static void	log_lldi(t_cursor *cursor,
							int32_t addr_1,
							int32_t addr_2,
							int32_t r_id)
{
	ft_printf("P %4d | lldi %d %d r%d\n", cursor->id, addr_1, addr_2, r_id);
	ft_printf("       | -> load from %d + %d = %d (with next_op %d)\n",
											addr_1,
											addr_2,
											addr_1 + addr_2,
											cursor->next_op + (addr_1 + addr_2));
}

void				op_lldi(t_vm *vm, t_cursor *cursor)
{
	int32_t	addr_1;
	int32_t	addr_2;
	int32_t	r_id;

	cursor->step += OP_CODE_LEN + ARGS_CODE_LEN;
	addr_1 = get_op_arg(vm, cursor, 1, true);
	addr_2 = get_op_arg(vm, cursor, 2, true);
	r_id = get_byte(vm, cursor->next_op, cursor->step);
	cursor->registers[INDEX(r_id)] = bytecode_to_int32(vm->arena,
			cursor->next_op + (addr_1 + addr_2), DIR_SIZE);
	cursor->step += REG_LEN;
	if (vm->log & OP_LOG)
		log_lldi(cursor, addr_1, addr_2, r_id);
}
