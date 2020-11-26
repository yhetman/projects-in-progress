#include "lexer.h"
#include "t_automate.h"

int 	t_automatePunctuation(t_automate *a , char c) {
	if (is_Comment == 1 || is_String == 1)
		(*a).state = -1;
    switch((*a).state) {
        case 0:
            if(c == ';' || c == '.' || c== ',') {
                sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state=1;
                return 0;
            }
			if (c == ' ' || c == '\n')
				return 0;
            return 0;
            break;
        case 1:
            if(((int)c)>=48 && ((int)c)<=57) {
                return 0;
            } else {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Punctuation Sign");
				lexema((*a).buffer, "Punctuation Sign");
				fseek(source, -1, SEEK_CUR);
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
