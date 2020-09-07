/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 19:49:18 by vbrazhni          #+#    #+#             */
/*   Updated: 2019/01/03 02:00:35 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "corewar_vs.h"

static void	handle_buttons(t_vm *vm)
{
	if (vm->vs->button == SPACE)
		vm->vs->is_running = !(vm->vs->is_running);
	else if (vm->vs->button == MUSIC)
		vm->vs->sounds = !(vm->vs->sounds);
	else if (vm->vs->button == DISPLAY_HELP)
		vm->vs->display_help = !(vm->vs->display_help);
	else if (vm->vs->button == SPEED_UP_1)
		vm->vs->speed++;
	else if (vm->vs->button == SPEED_UP_10)
		vm->vs->speed += 10;
	else if (vm->vs->button == SPEED_UP_100)
		vm->vs->speed += 100;
	else if (vm->vs->button == SPEED_DOWN_1)
		vm->vs->speed--;
	else if (vm->vs->button == SPEED_DOWN_10)
		vm->vs->speed -= 10;
	else if (vm->vs->button == SPEED_DOWN_100)
		vm->vs->speed -= 100;
	else if (vm->vs->button == SPEED_DEFAULT)
		vm->vs->speed = DEFAULT_SPEED;
	vm->vs->is_running = (!vm->amount_of_cursors) ? false : vm->vs->is_running;
	vm->vs->speed = (vm->vs->speed < 1) ? 1 : vm->vs->speed;
	vm->vs->speed = (vm->vs->speed > 1000) ? 1000 : vm->vs->speed;
}

static void	exec_cycle_vs(t_vm *vm)
{
	size_t amount_of_cursors;

	if (vm->amount_of_cursors)
	{
		exec_cycle(vm);
		if (vm->cyc_reminder == vm->cycles_after_check
			|| vm->cyc_reminder <= 0)
		{
			amount_of_cursors = vm->amount_of_cursors;
			cycles_to_die_check(vm);
			if (amount_of_cursors != vm->amount_of_cursors && vm->amount_of_cursors)
				play_death_sound(vm);
		}
		if (!vm->amount_of_cursors)
		{
			play_victory_sound(vm);
			vm->vs->is_running = false;
		}
	}
}

void		exec_vs(t_vm *vm)
{
	int32_t i;

	i = 0;
	while (i < vm->amount_of_champs)
		clear_name(vm->champs[i++]->name);
	configure_vs(vm);
	while ((vm->vs->button = getch()) != ESC)
	{
		handle_buttons(vm);
		if (vm->vs->button == PASS_ONE_CYCLE)
			exec_cycle_vs(vm);
		else if (vm->vs->is_running && (clock() >= calc_time_delay(vm)))
		{
			vm->vs->time = clock();
			exec_cycle_vs(vm);
		}
		draw(vm);
	}
	free_vs(&(vm->vs));
}
