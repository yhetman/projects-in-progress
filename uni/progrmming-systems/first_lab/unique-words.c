/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique-words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 23:14:13 by yhetman           #+#    #+#             */
/*   Updated: 2020/09/16 23:56:43 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char 		*read_file(char *argv)
{
	char 			*file;
    FILE			*fd;

	if (!(fd = fopen(argv, "r")))
        return (NULL);
	fseek(fd, 0, SEEK_END);
	long fsize = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	file = malloc(fsize + 1);
	fread(file, 1, fsize, fd);
	fclose(fd);
	file[fsize] = 0;
	return (file);
}


static bool			unique_characters(char *string)
{
	int 			i,
					j,
					length;

	length = strlen(string);
	for (i = 0; i < length - 1; i++)
        for (j = i + 1; j < length; j++)
            if (string[i] == string[j]) 
                return (false);
    return (true); 
}

int					main(int argc, char **argv)
{
    char			**unique_words,
    	 			*file;
    int 			i = -1,
    				resulting_words = 0;

    if(!(file = read_file(argv[1])))
    	return (write(STDERR, "No file\n", 8));
    unique_words = find_unique_words_parser(file);
    printf("\t RESULT\n");
    while (unique_words[++i])
    	if (unique_characters(unique_words[i]))
    	{
        	printf("\t|%s|\n",
        	unique_words[i]);
        	resulting_words++;
        }
    printf("Amount of unique words : %d\n", i - 1);
    printf("Amount of words with unique characters: %d\n", resulting_words);
    if (file)
        free(file);
    exit(EXIT_SUCCESS);
}
