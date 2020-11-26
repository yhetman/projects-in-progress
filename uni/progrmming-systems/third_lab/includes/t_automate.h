#ifndef T_AUTOMATE_H
#define T_AUTOMATE_H

# include <stdio.h>

typedef struct 	s_automate
{
	char 		buffer[BUFSIZ];
	int 		state;
	int 		(*function)(struct s_automate *a,char c);
}				t_automate;

#endif