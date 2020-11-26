#include "lexer.h"
#include "t_automate.h"


int 	t_automateAsignationOperator(t_automate *a, char c){
	if (is_Comment == 1)
		(*a).state = -1;
	switch((*a).state){
		case 0:
			if(c == '*' || c == '/' || c == '%') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 1;
				return 0;
			}
			if(c == '=') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 2;
				return 0;
			}
			if (c == '+') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 3;
				return 0;
			}
			if (c == '-') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 4;
				return 0;
			}
			if (c == ' ' || c == '\n')
				return 0;
			(*a).state = -1;
			break;
		case 1:
			if(c == '=') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Assignment operator");
				lexema((*a).buffer, "Assignment operator");
				return 1;
			}
			(*a).state = -1;
			return 0;
			break;
		case 2:
			fprintf(stdout, "%s\t%s\n",(*a).buffer,"Assignment operator");
			lexema((*a).buffer, "Assignment operator");
			fseek(source, -1, SEEK_CUR);
			return 1;
			break;
		case 3:
			if(c == '+') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Assignment operator");
				lexema((*a).buffer, "Assignment operator");
				return 1;
			}
			(*a).state = -1;
			return 0;
			break;
		case 4:
			if(c == '-') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Assignment operator");
				lexema((*a).buffer, "Assignment operator");
				return 1;
			}
			(*a).state = -1;
			return 0;
			break;
	}
	return 0;
}


