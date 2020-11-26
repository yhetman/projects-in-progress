#include "lexer.h"
#include "consts.h"

int 		isKeyword(char str[])
{
	int 	size,
			i;

	size = sizeof(keywords) / sizeof(keywords[1]);
	for (i = 0; i < size; i++)
		if (strcmp(str, keywords[i]) == 0)
			return 1;
	return 0;
}


int 		isPreprosessor(char str[])
{
	int 	size,
			i;

	size = sizeof(preprosessors) / sizeof(preprosessors[1]);
	for (i = 0; i < size; i++)
		if (strcmp(str, preprosessors[i]) == 0)
			return 1;
	return 0;
}


int 		isDataType(char str[])
{
	int 	size,
			i;

	size = sizeof(dataType) / sizeof(dataType[1]);
	for (i = 0; i < size; i++)
		if (strcmp(str, dataType[i]) == 0)
			return 1;
	return 0;
}
