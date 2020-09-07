/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 02:37:30 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/26 03:38:56 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

nclude "corewar.h"

static inline bool	is_cor(const char *file)
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
	return (vm);
}

static void	check_dump(int *argc, char ***argv, t_vm *vm)
{
	if (!vm->dump_print_mode && *argc >= 2
			&& IS_INT(*(*argv + 1)))
	{
		if ((vm->dump_cycle = ft_atoi(*(*argv + 1))) < 0)
			vm->dump_cycle = -1;
		vm->dump_print_mode = ((!ft_strcmp(**argv, "-d")) ? 64 : 32);
		(*argc) -= 2;
		(*argv) += 2;
	}
	else
		usage();
}

static int	start_virtual_machine(t_vm *vm)
{
	long			id;
	unsigned long	next_op;

	id = 0;
	next_op = 0;
	if (vm->amount_of_champs < 1
			|| vm->amount_of_champs > MAX_PLAYERS)
		vm_exit("| WRONG NUMBER OF PLAYERS |\n", &vm);
	while (++id <= vm->amount_of_champs)
	{
		if (!(vm->champs[INDEX(id)] = get_champion(champs, id)))
			usage(0);
		ft_memcpy(&(vm->arena[next_op]), vm->champs[INDEX(id)]->code,
				(size_t)(vm->champs[INDEX(id)]->code_size));
		next_op += MEM_SIZE / vm->amount_of_champs;
	}
	vm->alive = vm->champs[INDEX(vm->amount_of_champs)];
	set_cursors(vm);
	print_intro(vm->champs, vm->amount_of_champs);
	exec(vm);
}

int			main(int ac, char **av)
{
	t_vm		*vm;
	t_champion	*champs;

	ac--;
	av++;
	champs = NULL;
	if (!ac)
		usage();
	vm = malloc_vm(vm);
	while (ac)
	{
		if (!ft_strcmp(*av, "-dump"))
			check_dump(&ac, &av, vm);
		else if (!ft_strcmp(*av, "-n")
				|| is_cor(*av))
			check_file(&ac, &av, vm, &champs);
		else
			usage();
	}
	start_virtual_machine(vm, champs);
	vm_exit(print_last_alive(vm), &vm);
	return (0);
}
						
