#include "lexer.h"



void 	lexema(char *l, char *t)
{
	memset(writer, '\0', BUFSIZ);
    sprintf(writer,"%s\t%s\n", l, t);
    write(fd_lexems, writer, BUFSIZ);
}



void 	table(char *l)
{
	memset(writer, '\0', BUFSIZ);
    sprintf(writer,"%s\n", l);
    write(fd_table, writer, BUFSIZ);
}
