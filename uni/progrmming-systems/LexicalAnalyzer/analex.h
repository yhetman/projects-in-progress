#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#define numberAutomates 12

FILE 	*source;
char 	writer[BUFSIZ];

char 			*keywords[24] = {"auto", "struct", "break", "else", "switch", "case", "enum",
						"register", "typedef", "extern", "return", "union",
						"const", "continue", "for", "void", "default", "goto",
						"sizeof", "volatile", "do", "if", "static", "while" };


char 			*dataType[10] = {"char", "int", "float", "double", "short", "long", "unsigned",
						"signed", "enum", "const" };

char 			*preprosessors[5] = {"define", "ifndef", "include", "endif", "ifdef"};

int 			is_Comment,
				is_String,
				fd_lexems,
				fd_table;


typedef struct 	s_automate
{
	char 		buffer[BUFSIZ];
	int 		state;
	int 		(*function)(struct s_automate *a,char c);
}				t_automate;


void			reset(t_automate array[])
{
    int 		i;

    for(i = 0; i < numberAutomates; i++)
    {
        array[i].state = 0;
        memset(array[i].buffer, '\0', BUFSIZ);
    }
	is_Comment = 0;
	is_String = 0;
}

int 			getLastIndex(char buffer[])
{
	int 		i;

	i = 0;
	while(buffer[i] != '\0')
	{
		i++;
		if (i >= (BUFSIZ))
			break;
	}
	return i;
}


int 			isKeyword(char str[])
{
	int 		size,
				i;

	size = sizeof(keywords) / sizeof(keywords[1]);
	for (i = 0; i < size; i++)
		if (strcmp(str, keywords[i]) == 0)
			return 1;
	return 0;
}

int 			isPreprosessor(char str[])
{
	int 		size,
				i;

	size = sizeof(preprosessors) / sizeof(preprosessors[1]);
	for (i = 0; i < size; i++)
		if (strcmp(str, preprosessors[i]) == 0)
			return 1;
	return 0;
}

int 			isDataType(char str[])
{
	int 		size,
				i;

	size = sizeof(dataType) / sizeof(dataType[1]);
	for (i = 0; i < size; i++)
		if (strcmp(str, dataType[i]) == 0)
			return 1;
	return 0;
}


void 			lexema(char *l, char *t)
{
	memset(writer, '\0', BUFSIZ);
    sprintf(writer,"%s\t%s\n", l, t);
    write(fd_lexems, writer, BUFSIZ);
}



void 			table(char *l)
{
	memset(writer, '\0', BUFSIZ);
    sprintf(writer,"%s\n", l);
    write(fd_table, writer, BUFSIZ);
}


/****************************************************\
 *													*
 *					t_automates						*
 *													*
\****************************************************/


int 			t_automateRealNumber(t_automate *a , char c) {
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



int 			t_automateNumber(t_automate *a , char c) {
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



int 			t_automateIdentificator(t_automate *a , char c) {
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



int 			t_automatePreprosessor(t_automate *a, char c) {
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



int 			t_automatePunctuation(t_automate *a , char c) {
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



int 			t_automateAsignationOperator(t_automate *a, char c){
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



int 			t_automateGroupingOperator(t_automate *a , char c) {
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




int 			t_automateArithmeticOperator(t_automate *a , char c) {
	if (is_Comment == 1 || is_String == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if (((c == '+') || (c == '-') || (c == '/') || (c == '%')) && is_Comment == 0) {
				(*a).state = 1;
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			}
			if (c == '*') {
				(*a).state = 2;
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				return 0;
			}
			return 0;
		case 1:
			if ((isdigit(c) || c == ' ' || isalpha(c)) && is_Comment == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Arithmetic operator");
				lexema((*a).buffer, "Arithmetic operator");
				fseek(source, -1, SEEK_CUR);
				return 1;
			}
			return 0;
			break;
		case 2:
			if ((isdigit(c) || c == ' ' || isalpha(c)) && is_Comment == 0) {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Arithmetic Operator or pointer");
				lexema((*a).buffer, "Arithmetic Operator or pointer");
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



int 			t_automateCharString(t_automate *a , char c) {
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
}




int 			t_automateComparisonOperator(t_automate *a , char c) {
	if (is_Comment == 1)
		(*a).state = -1;
	switch ((*a).state) {
		case 0:
			if (c == '=') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 1;
				return 0;
			}
			if (c == '!') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 1;
				return 0;
			}
			if (c == '>') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 2;
				return 0;
			}
			if (c == '<') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				(*a).state = 2;
				return 0;
			}
			if (c == ' ' || c == '\n')
				return 0;
			(*a).state = -1;
			return 0;
			break;
		case 1:
			if (c == '=') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operator of comparison");
				lexema((*a).buffer, "Operator of comparison");
				return 1;
			}
			(*a).state = -1;
			return 0;
			break;
		case 2:
			if (c == '=') {
				sprintf((*a).buffer + getLastIndex((*a).buffer), "%c", c);
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operator of comparison");
				lexema((*a).buffer, "Operator of comparison");
				return 1;
			} else {
				fprintf(stdout, "%s\t%s\n",(*a).buffer,"Operator of comparison");
				lexema((*a).buffer, "Operator of comparison");
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
