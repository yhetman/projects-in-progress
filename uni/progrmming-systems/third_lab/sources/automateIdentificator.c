#include "lexer.h"
#include "t_automate.h"

int 	t_automateIdentificator(t_automate *a , char c) {
	if (is_Comment == 1 || is_String == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if (isalpha(c) || c == '_') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 1;
				return 0;
			}
			if (c == ' ' || c == '\n')
				return 0;
			(*a).state = -1;
			return 0;
			break;
		case 1:
			if (isdigit(c) || isalpha(c) || c == '_') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			} else {
				if (isKeyword((*a).buffer)) {
					fprintf(stdout, "%s\t%s\n",(*a).buffer,"Reserved word");
					lexema((*a).buffer, "Reserved word");
				} else if (isDataType((*a).buffer)) {
					fprintf(stdout, "%s\t%s\n",(*a).buffer,"Reserved word - Data Type");
					lexema((*a).buffer, "Reserved word - Data Type");
				} else {
					fprintf(stdout, "%s\t%s\n",(*a).buffer,"Identificator");
					lexema((*a).buffer, "Identificator");
				}
				table((*a).buffer);
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

