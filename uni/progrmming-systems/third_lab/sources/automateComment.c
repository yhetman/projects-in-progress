#include "lexer.h"
#include "t_automate.h"

int 			t_automateComment(t_automate *a, char c) {
	switch((*a).state) {
        case 0:
            if(c == '/') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
                (*a).state = 1;
                return 0;
            }
        	return 0;
        	break;
    	case 1:
			if(c == '/') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
    		 	(*a).state = 2;
				is_Comment = 1;
    		 	return 0;
    		} if(c == '*') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
    			(*a).state = 3;
				is_Comment = 1;
    			return 0;
    		}
            return 0;
            break; 
        case 2:
        	if(((int)c) != 10) {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 2;
				return 0;
        	} else {
      		    fprintf(stdout, "%s\t%s\n",(*a).buffer,"Comment");
				lexema((*a).buffer, "Comment");
				return 1;
      		}
			return 0;
			break;
      	case 3:
      		if(c == '*') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
      			(*a).state = 4;
      			return 0;
      		} else {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
      			(*a).state = 3;
      			return 0;
      		}
			return 0;
			break;
      	case 4:
			if(c == '*') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
      			(*a).state = 4;
      			return 0;
      		}
			if (c == '/') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Large Comment");
				lexema((*a).buffer, "Large Comment");
				return 1;
			} else {
				printf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
      			(*a).state = 3;
      			return 0;
			}
			return 0;
			break;
        default:
			return 0;
			break;
	}
}
