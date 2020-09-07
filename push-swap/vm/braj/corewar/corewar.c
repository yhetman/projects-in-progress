/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:10:02 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/12/26 12:25:11 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static bool	is_cor(const char *file)
{
	return ((file && ft_strlen(file) >= 4)
	 ? (!ft_strcmp(ft_strchr(file, '\0') - 4, ".cor"))
	 	: (false));
}

static t_vm	*malloc_vm(t_vm *vm)
{
	if (!(vm = (t_vm *)ft_memalloc(sizeof(t_vm))))
		vm_exit("| MEMORY ALLOCAION FAILED |\n", NULL);
	ft_bzero(vm, sizeof(t_vm));
	vm->cyc_reminder = CYCLE_TO_DIE;
	vm->dump_cycle = -1;
	//vm->show_cycle = -1;
	return (vm);
}

static void	check_file(int *ac, char ***av, t_vm *vm, t_champion **champs)
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

int start_virtual_machine(int ac, char **av)
{
	t_vm		*vm;
	t_champion	*champs

	vm = malloc_vm(vm);
	while (ac)
	{
		if (!ft_strcmp(*av, "-dump"))
			check_dump(&ac, &av, vm);
		else if (!ft_strcmp(*av, "-n") || is_cor(*av))
			check_file(&ac, &av, vm, &champs);
		else
			usage();
	}
	if (vm->amount_of_champs < 1
	|| vm->amount_of_champs > MAX_PLAYERS)
		vm_exit("| WRONG NUMBER OF PLAYERS |\n", vm));
	set_champs(vm, champs);
	init_arena(vm);
	set_cursors(vm);
	print_intro(vm->champs, vm->amount_of_champs);
	exec(vm);
	vm_exit(print_last_alive(vm), &vm);
}

int			main(int ac, char **av)
{
	if (argc > 1)
		start_virtual_machine(--argc, ++argv);
	else
		usage();
	return (0);
}
