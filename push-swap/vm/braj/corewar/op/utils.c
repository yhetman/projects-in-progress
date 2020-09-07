/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:33:19 by ablizniu          #+#    #+#             */
/*   Updated: 2018/12/26 13:10:49 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_op.h"
#include "corewar_vs.h"

int32_t		bytecode_to_int32(const uint8_t *arena, int32_t addr, int32_t size)
{
	int32_t		result;
	t_bool		sign;
	int			i;

	result = 0;
	sign = (t_bool)(arena[calc_addr(addr)] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((arena[calc_addr(addr + size - 1)] ^ 0xFF) << (i++ * 8));
		else
			result += arena[calc_addr(addr + size - 1)] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

void		int32_to_bytecode(uint8_t *arena, int32_t addr, int32_t value,
						int32_t size)
{
	int8_t i;

	i = 0;
	while (size)
	{
		arena[calc_addr(addr + size - 1)] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

int32_t		get_op_arg(t_vm *vm, t_cursor *cursor, uint8_t index, t_bool mod)
{
	t_op		*op;
	int32_t		value;
	int32_t		addr;

	op = &g_op[INDEX(cursor->op_code)];
	value = 0;
	if (cursor->args[INDEX(index)] & T_REG)
		value = cursor->registers[INDEX(get_byte(vm, cursor->next_op, cursor->step))];
	else if (cursor->args[INDEX(index)] & T_DIR)
		value = bytecode_to_int32(vm->arena,
								cursor->next_op + cursor->step,
								op->t_dir_size);
	else if (cursor->args[INDEX(index)] & T_IND)
	{
		addr = bytecode_to_int32(vm->arena,
								cursor->next_op + cursor->step,
								IND_SIZE);
		value = bytecode_to_int32(vm->arena,
							cursor->next_op + (mod ? (addr % IDX_MOD) : addr),
							DIR_SIZE);
	}
	cursor->step += step_size(cursor->args[INDEX(index)], op);
	return (value);
}

t_cursor	*duplicate_cursor(t_cursor *cursor, int32_t addr)
{
	t_cursor	*new;
	int			i;

	addr = calc_addr(cursor->next_op + addr);
	new = init_cursor(cursor->champ, addr);
	i = 0;
	while (i < REG_NUMBER)
	{
		new->registers[i] = cursor->registers[i];
		i++;
	}
	new->carry = cursor->carry;
	new->cycle_live = cursor->cycle_live;
	return (new);
}

void		update_map(t_vm *vm, t_cursor *cursor, int32_t addr, int32_t size)
{
	int32_t value;

	value = ((cursor->champ->id - 1) % MAX_PLAYER_ID) + 1;
	while (size)
	{
		vm->vs->map[calc_addr(addr + size - 1)].index = value;
		vm->vs->map[calc_addr(addr
								+ size - 1)].wait_cycles_store = CYCLE_TO_WAIT;
		size--;
	}
}
