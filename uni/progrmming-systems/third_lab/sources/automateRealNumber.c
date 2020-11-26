#include "lexer.h"
#include "t_automate.h"

int 	t_automateRealNumber(t_automate *a , char c) {
	if (is_Comment == 1 || is_String == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if (c == '+' || c == '-') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 2;
				return 0;
			}
			if (isdigit(c)) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 1;
				return 0;
			}
			if (c == '.') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 3;
				return 0;
			}
			return 0;
			break;
		case 1:
			if (isdigit(c)) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			}
			if (c == '.') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 3;
				return 0;
			}
			return 0;
			break;
		case 2:
			if (isdigit(c)) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 1;
				return 0;
			}
			
			return 0;
			break;
		case 3:
			if (isdigit(c)) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 4;
				return 0;
			}
			return 0;
			break;
		case 4:
			if (isdigit(c)) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Real Number");
				lexema((*a).buffer, "Real Number");
				fseek(source, -1, SEEK_CUR);
				return 1;
			}
			break;
		default:
			return 0;
			break;
	}
}
