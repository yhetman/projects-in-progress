#include "lexer.h"
#include "t_automate.h"


int 			main(int argc, const char * argv[]) {
	
	char 		c;

	t_automate 	t_automates[numberAutomates];
	
    if (argc != 2) { 
		fprintf(stderr, "Usage: %s source code\n", argv[0]);
		return -1;
	}
	if((source = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Error al abrir el archivo: %s", argv[1]);
		return -1;
	}
	if ((fd_lexems = open("lexems.txt", O_WRONLY | O_CREAT | O_TRUNC,0666)) < 0) { 
		fprintf(stderr, "Error creating archive lexems.txt"); 
		return -1;
	}
	if ((fd_table = open("tabel_symbols.txt", O_WRONLY | O_CREAT | O_TRUNC,0666)) < 0) { 
		fprintf(stderr, "Error creating archive tabel_symbols.txt"); 
		return -1;
	}

	t_automates[0].function = t_automateComment;
	t_automates[1].function = t_automateIdentificator;
	t_automates[2].function = t_automateLogicalOperator;
	t_automates[3].function = t_automateComparisonOperator;
	t_automates[4].function = t_automateAsignationOperator;
	t_automates[5].function = t_automateRealNumber;
	t_automates[6].function = t_automateNumber;
	t_automates[7].function = t_automatePunctuation;
	t_automates[8].function = t_automateCharString;
	t_automates[9].function = t_automateGroupingOperator;
	t_automates[10].function = t_automateArithmeticOperator;
	t_automates[11].function = t_automatePreprosessor;
	
	reset(t_automates);
	while ((c = getc(source)) != EOF) {
		if ((int)c == 10) {
		}
		
		if (t_automates[0].function(&t_automates[0], c) == 1) {
			reset(t_automates);
			continue;
		}
		if (t_automates[1].function(&t_automates[1], c) == 1) {
			reset(t_automates);
			continue;
		}
		if (t_automates[2].function(&t_automates[2], c) == 1) {
			reset(t_automates);
			continue;
		}
		if (t_automates[3].function(&t_automates[3], c) == 1) {
			reset(t_automates);
			continue;
		}
		if (t_automates[4].function(&t_automates[4], c) == 1) {
			reset(t_automates);
			continue;
		}
		if (t_automates[5].function(&t_automates[5], c) == 1) {
			reset(t_automates);
			continue;
		}
		if (t_automates[6].function(&t_automates[6], c) == 1) {
			reset(t_automates);
			continue;
		}
		
		if (t_automates[7].function(&t_automates[7], c) == 1) {
			reset(t_automates);
			continue;
		}
		
		if (t_automates[8].function(&t_automates[8], c) == 1) {
			reset(t_automates);
			continue;
		}
		
		if (t_automates[9].function(&t_automates[9], c) == 1) {
			reset(t_automates);
			continue;
		}
		
		if (t_automates[10].function(&t_automates[10], c) == 1) {
			reset(t_automates);
			continue;
		}
		if (t_automates[11].function(&t_automates[11], c) == 1) {
			reset(t_automates);
			continue;
		}
		fclose(source);
		return 0;
	}
}



