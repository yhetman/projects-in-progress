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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define 	MAX_LENGTH 	30
//#define 	_GNU_SOURCE
#define 	WORD_CHARS 	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`'-@1234567890"

static char			*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))) || !s)
		return (NULL);
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

static int			define_word(char const *s, unsigned int i)
{
	unsigned int 	length;

	length = 0;
	while (s[i] && (strchr(WORD_CHARS, s[i])))
	{
		++length;
		++i;
	}
	return (length);
}


static int			number_of_words(char const *s)
{
	unsigned int	words;

	words = 0;
	while (*s)
	{
		if (!(strchr(WORD_CHARS,  *s)))
			++s;
		else
		{
			++words;
			while (*s && (strchr(WORD_CHARS, *s)))
				++s;
		}
	}
	return (words);
}

void				ft_free_grid(char **line)
{
	int				i;

	i = -1;
	while (line[++i])
		free(line[i]);
}

char 				**find_unique_words(char **array_of_strs, int size)
{
	int 			i,
					j,
					k,
					unique_count;
	char 			**unique_words;

	unique_count = 0;
	for (i = 0; i < size; i++)
	{
    	for (j = i + 1; j < size; j++)
        	if (strcmp(array_of_strs[i], array_of_strs[j]) == 0)
            	break;
    	if (j == size)
        	unique_count++;
    }
    unique_words = (char **)malloc(sizeof(char *) * (unique_count + 1));
    for (i = 0, k = 0; i < size; i++)
	{
    	for (j = i + 1; j < size; j++)
        	if (strcmp(array_of_strs[i], array_of_strs[j]) == 0)
            	break;
    	if (j == size)
        	unique_words[k++] = ft_strsub(array_of_strs[i], 0, strlen(array_of_strs[i]));
    }
    ft_free_grid(array_of_strs);
    return(unique_words);
}

char				**find_unique_words_parser(char const *s)
{
	char			**splited_str;
	unsigned int	i,
					j;
	int				length,
		 			amount_of_words;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	amount_of_words = number_of_words(s);
	if (!(splited_str = (char **)malloc(sizeof(char *) *
		(amount_of_words + 1))))
		return (NULL);
	while (s[i])
	{
		if (strchr(WORD_CHARS, s[i]))
		{
			length = define_word(s, i);
			if (length > MAX_LENGTH)
				splited_str[j++] = ft_strsub(s, i, MAX_LENGTH);
			else
				splited_str[j++] = ft_strsub(s, i, length);
			i += length;
		}
		else
			i++;
	}
	splited_str[j] = NULL;
	return (find_unique_words(splited_str, amount_of_words));
}


char 				*read_file(char *argv)
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
int					main(int argc, char **argv)
{
//    FILE			*fd;
    char			**unique_words,
    	 			*file;
    int 			i =0;

//    if (!(fd = fopen(argv[1], "r")))
//        return (write(2, "No file", 8));
//
//	fseek(fd, 0, SEEK_END);
//	long fsize = ftell(fd);
//	fseek(fd, 0, SEEK_SET);
//
//	string = malloc(fsize + 1);
//    fread(string, 1, fsize, fd);
//	fclose(fd);
    if(!(file = read_file(argv[1])))
    	return (write(2, "No file", 8));
    unique_words = find_unique_words_parser(file);
    while (unique_words[i])
        printf("Retrieved line of length %zu: unique words: %s\n", strlen(file), unique_words[i++]);
    if (file)
        free(file);
    exit(EXIT_SUCCESS);
}

