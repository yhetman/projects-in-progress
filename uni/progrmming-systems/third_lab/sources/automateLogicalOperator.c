#include "lexer.h"
#include "t_automate.h"


int 			t_automateLogicalOperator(t_automate *a , char c) {
	if (is_Comment == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if (c == '&') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 1;
				return 0;
			}
			if (c == '|') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 2;
				return 0;
			}
			if (c == '!') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Logical operator");
				lexema((*a).buffer, "Logical operator");
				return 1;
			}
			if (c == ' ' || c == '\n')
				return 0;
			(*a).state = -1;
			return 0;
			break;
		case 1:
			if (c == '&') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Logical operator");
				lexema((*a).buffer, "Logical operator");
				return 1;
			}
			(*a).state = -1;
			return 0;
			break;
		case 2:
			if (c == '|') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Logical operator");
				lexema((*a).buffer, "Logical operator");
				return 1;
			}
			(*a).state = -1;
			return 0;
			break;
		default:
			return 0;
			break;
	}
}
