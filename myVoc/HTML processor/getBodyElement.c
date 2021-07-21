#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX		1024000

int main(int argc, char * argv[]) {
	FILE * in, * out;
	int ch1, ch2;
	int chs[MAX], * pc = chs;
	int i,j = 0;
	bool ltf = false, bf = false, of = false, df = false, yf = false;
		// tf = less than (<) found; b ... o ... d ... y ... the same
	if (argc < 2) {
		fprintf(stderr, "Usage: %s FILE\n", argv[0]);
		exit(1);
	}
	if ((in = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Error opening %s\n", argv[1]);
		exit(1);
	}

	while ((ch1 = getc(in)) != EOF) {
		
		if (ch1 == 0x3C && (ch2 = getc(in)) == 0x0) { // '<' encountered
			if(!ltf) {
				*pc = ch1;
                putchar(ch1);
				ltf = true;
				j++;
			} 
			if ((ch1 = getc(in)) == 0x42 && (ch2 = getc(in)) == 0x0) { // 'B' encountered
				if(!bf) {
					++pc;
					*pc = ch1;
					bf = true;
					j++;
				}
				if ((ch1 = getc(in)) == 0x4F && (ch2 = getc(in)) == 0x0) { // 'O' encountered
					if (!of) {
						++pc;
						*pc = ch1;
						of = true;
						j++;
					}
					if((ch1 = getc(in)) == 0x44 && (ch2 = getc(in)) == 0x0) { // 'D' encountered
						if (!df) {
							++pc;
							*pc = ch1;
							df = true;
							j++;
						}
						if((ch1 = getc(in)) == 0x59 && (ch2 = getc(in)) == 0x0) { // 'Y' encountered
							if (!yf) {
								++pc;
								*pc = ch1;
								yf = true;
								j++;
							}
							++pc;
							break;
						}
					}
				}
			}	
		}
	}
	if (yf) {
        if ((out = fopen("temp2.htm", "w")) == NULL) {
            fprintf(stderr, "Error creating %s\n", "temp2.htm");
            exit(1);
        }
		while((ch1 = getc(in)) != EOF) {
			*pc = ch1;
			pc++;
			j++;
		}
		*pc = '\0';
		for (i = 0; i < j; i++)
			if (chs[i] != 0x0)
				fprintf(out,"%c", chs[i]);
	}
	else {
		fprintf(stderr, "Can't find <BODY in %s\n", argv[1]);
		exit(1);
	}

	fclose(in);
	fclose(out);
	return 0;
}
