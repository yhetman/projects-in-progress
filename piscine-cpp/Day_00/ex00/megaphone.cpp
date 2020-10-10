/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:46:01 by yhetman           #+#    #+#             */
/*   Updated: 2019/11/30 19:05:36 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void	output_feedback(char **argv, int i)
{
	int	j;

	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] >= 'a' && argv[i][j] <= 'z')
				argv[i][j] -= 32;
		std::cout << argv[i];
	}
	std::cout << std::endl;
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
		output_feedback(argv, 0);
	return (0);
}
