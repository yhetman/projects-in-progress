#include "lexer.h"
#include "t_automate.h"


int 	t_automateArithmeticOperator(t_automate *a , char c) {
	if (is_Comment == 1 || is_String == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if (((c == '+') || (c == '-') || (c == '/') || (c == '%')) && is_Comment == 0) {
				(*a).state = 1;
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			}
			if (c == '*') {
				(*a).state = 2;
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			}
			return 0;
		case 1:
			if ((isdigit(c) || c == ' ' || isalpha(c)) && is_Comment == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Arithmetic operator");
				lexema((*a).buffer, "Arithmetic operator");
				fseek(source, -1, SEEK_CUR);
				return 1;
			}
			return 0;
			break;
		case 2:
			if ((isdigit(c) || c == ' ' || isalpha(c)) && is_Comment == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Arithmetic Operator or pointer");
				lexema((*a).buffer, "Arithmetic Operator or pointer");
				fseek(source, -1, SEEK_CUR);
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}
