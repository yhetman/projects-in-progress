#include "lexer.h"
#include "t_automate.h"

int 	t_automatePreprosessor(t_automate *a, char c) {
	if (is_Comment == 1 || is_String == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if (c == '#') {
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
				if (isPreprosessor((*a).buffer)) {
					fprintf(stdout, "%s\t%s\n",(*a).buffer,"Preprosessor Directive");
					lexema((*a).buffer, "Preprosessor Directive");
				} else {
					fprintf(stdout, "%s\t%s\n",(*a).buffer,"Preprosessor Directive");
					lexema((*a).buffer, "Preprosessor Directive");
				}
				table((*a).buffer);
				fseek(source, -1, SEEK_CUR);
				return 1;
			}
			return 0;
			break ;
		default:
			return 0;
			break;
	}
}
