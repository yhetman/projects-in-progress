#ifndef LEXER_H
#define LEXER_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <fcntl.h>
# include <unistd.h>
# include "t_automate.h"
# define numberAutomates 12

FILE 			*source;
char 			writer[BUFSIZ];

int 			is_Comment,
				is_String,
				fd_lexems,
				fd_table;


void			reset(t_automate array[]);
int 			getLastIndex(char buffer[]);
int 			isKeyword(char str[]);
int 			isPreprosessor(char str[]);
int 			isDataType(char str[]);
void 			lexema(char *l, char *t);
void 			table(char *l);

/****************************************************\
 *													*
 *					t_automates						*
 *													*
\****************************************************/


int 			t_automateRealNumber(t_automate *a , char c);

int 			t_automateNumber(t_automate *a , char c);

int 			t_automateIdentificator(t_automate *a , char c);

int 			t_automatePreprosessor(t_automate *a, char c);

int 			t_automateComment(t_automate *a, char c);

int 			t_automatePunctuation(t_automate *a , char c);

int 			t_automateAsignationOperator(t_automate *a, char c);

int 			t_automateGroupingOperator(t_automate *a , char c);

int 			t_automateArithmeticOperator(t_automate *a , char c);

int 			t_automateCharString(t_automate *a , char c);

int 			t_automateComparisonOperator(t_automate *a , char c);

int 			t_automateLogicalOperator(t_automate *a , char c);

#endif