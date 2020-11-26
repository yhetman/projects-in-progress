#include "lexer.h"
#include "t_automate.h"

int 	t_automateGroupingOperator(t_automate *a , char c) {
	if (is_Comment == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if ((c == '(') || (c == ')') || (c == '[') || (c == ']') || (c == '{') || (c == '}')) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Grouping operator");
				lexema((*a).buffer, "Grouping operator");
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}
