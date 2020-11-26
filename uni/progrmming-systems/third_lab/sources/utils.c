#include "lexer.h"
#include "t_automate.h"

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
