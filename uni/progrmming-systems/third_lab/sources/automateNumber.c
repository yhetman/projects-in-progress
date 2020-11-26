#include "lexer.h"
#include "t_automate.h"

int 	t_automateNumber(t_automate *a , char c) {
	if (is_Comment == 1 || is_String == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if (c == '+' || c == '-') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 1;
				return 0;
			}
			if (isdigit(c)) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 2;
				return 0;
			}
			return 0;
			break;
		case 1:
			if (isdigit(c)) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 2;
				return 0;
			}
			(*a).state = -1;
			return 0;
			break;
		case 2:
			if (isdigit(c)) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else if (c != '.'){
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Natural Number");
				lexema((*a).buffer, "Natural Number");
				fseek(source, -1, SEEK_CUR);
				return 1;
			} else {
				(*a).state = -1;
				return 0;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}
