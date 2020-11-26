#include "lexer.h"
#include "t_automate.h"

int 			t_automateCharString(t_automate *a , char c)
{
	if (is_Comment == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if ((int)c == 34) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 1;
				is_String = 1;
				return 0;
			}
			if ((int)c == 39) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 2;
				is_String = 1;
				return 0;
			}
			if (c == ' ' || c == '\n')
				return 0;
			(*a).state = -1;
			break;
		case 1:
			if ((int)c != 34) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Character string");
				lexema((*a).buffer, "Character string");
				return 1;
			}
			return 0;
			break;
		case 2:
			if ((int)c != 39) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Char");
				lexema((*a).buffer, "Char");
				return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
	return 0;
}
