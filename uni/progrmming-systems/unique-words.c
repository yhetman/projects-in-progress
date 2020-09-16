/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique-words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 23:14:13 by yhetman           #+#    #+#             */
/*   Updated: 2020/09/16 23:56:43 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MAX_LENGTH 30

int main(int args, char **argv)
{	
	int	fd;
	int i = 0,j,k,l,p, space = 0;
	char *new_str;

	if(!(fd = fopen(argv[1],"r")))
		return(write(2, "No file", 8));

	while(read())
		print("ok")
	return (0);
}

