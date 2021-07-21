#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX						81
#define LEN						512

void getString (char * str1, unsigned strLen, const char * str2, char * str3, char * str4);
unsigned getNumberOfWordsInExample(const char * ex);
void fillWordArrayWithWordsInExample (const char * ex, char ** wds);
unsigned getLevenshteinDistance (const char * str1, const char * str2);
const char * findWordInExample(const char * entryWd, const char ** wds, const unsigned n);
void setValueForElementInMatrix (unsigned * firstPosition, unsigned row, unsigned col, unsigned pos, unsigned x);
unsigned * getPointerToValueInMatrix(unsigned * firstPosition, unsigned row, unsigned col, unsigned pos);
unsigned getElementInMatrix(unsigned * firstPosition, unsigned row, unsigned col, unsigned pos);
unsigned minimumValue(unsigned x, unsigned y, unsigned z);
bool exampleAssembler (const char * ex, const char * wordInExample, unsigned entryOrCollocation, char assembledExample[]); // entry = 1, collocation = 0
void getPartBeforeWord (const char * ex, const char * ptr2EntInEx, char savePartBeforeWord[]);
const char * getPartAfterWordInExample(const char * ptr2EntInEx, const char * entryWdInEx);
char * findPtrToWordInExample(const char * ex, const char * wordInExample);
void extractWord(const char * source, char * dest);
void freeMem(char ** ptr2Mem, unsigned num);
bool writeToHTMFile (const char * assembledEx, const char * htmFileName);

int main(int argc, char * argv[]) {
	char entryWord[MAX], collocation[MAX];
	char example[LEN];
	char ** words;
	const char * entryWordInExample, * collocationInExample;
	unsigned numberOfWordsInExample;
	int i;
	char assembledExample1[LEN], assembledExample2[LEN];
	bool success;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s htm file name\n", argv[0]);
		exit(1);
	}

	//while (1) {
		//getString(entryWord, MAX, "Enter the entry word: ");
		extractWord(argv[1], entryWord);
		getString(collocation, MAX, "Enter a collocation for ", entryWord, " (enter \"nc\" for none): ");
		getString(example, LEN, "Enter an example for ", entryWord, " (enter \"ne\" for none):\n");
		if (entryWord[0] == EOF || collocation[0] == EOF || example[0] == EOF) {
			puts("Bye!");
			exit(1);
		}
		if (strcmp(example, "ne") == 0) {
			puts(example);
			if (writeToHTMFile("No example found for this word", argv[1]) == true) {
				puts("Write to HTM file successful!");
			}
			else
				puts("Write to HTML file failed!");
			puts("Bye!");
			return 0;
			//continue;
		}
		// get index of entry word in the example	
		numberOfWordsInExample = getNumberOfWordsInExample(example);
		if (numberOfWordsInExample == 0){
			puts("Bye!");
			return 0;
		}
		numberOfWordsInExample += 1; // Words are one more than spaces in a sentence.
		words = (char **) malloc(sizeof (char *) * numberOfWordsInExample); // (char *) should include the () around char *
		for (i = 0; i < numberOfWordsInExample; i++)
			words[i] = (char *) malloc(sizeof (char *) * MAX);
		
		fillWordArrayWithWordsInExample(example, words); 
		entryWordInExample = findWordInExample(entryWord, (const char **)words, numberOfWordsInExample);
		success = exampleAssembler ((const char *)example, entryWordInExample, 1, assembledExample1);
		if (success == false) {
			puts("Can't find the enetry word in the example.");
			freeMem(words, numberOfWordsInExample);
			puts("Bye!");
			return 0;
		}
	
		if (strcmp(collocation, "na") != 0) {
			collocationInExample = findWordInExample(collocation, (const char **)words, numberOfWordsInExample);
			success = exampleAssembler ((const char *)assembledExample1, collocationInExample, 0, assembledExample2);
			if (success == false) {
				puts("Can't find the collocation word in the example.");
				freeMem(words, numberOfWordsInExample);
				puts("Bye!");
				return 0;
			}
			puts(assembledExample2);
			if (writeToHTMFile(assembledExample2, argv[1]) == true) {
				puts("Write to HTM file successful!");
			}
		}
		else {
			puts(assembledExample1);
			if (writeToHTMFile(assembledExample1, argv[1]) == true) {
				puts("Write to HTM file successful!");
			}
		}
	    freeMem(words, numberOfWordsInExample);
	//}
	puts("Bye!");
	return 0;
}

void getString(char * str1, unsigned strLen, const char * str2, char * str3, char * str4) {

	printf("%s%s%s", str2, str3, str4);
	fgets(str1, strLen, stdin);

	while (*str1 != '\n') {
		str1++;
	}
	*str1 = '\0';
}
void extractWord(const char * source, char * dest)
{
	int len = 0;

	while (*source) {
        source++;
        len++;
    } // Go to the end of source and get the length of source
    while (len != 0) {
        if (*source == '/') {
            source++;
            break;
        }
        source--;
        len--;
    }
	while (*source) { 
    // Frist strip off the head

    	if((tolower(*source) >= 'a' && tolower(*source) <= 'z') && *(source+1) != '_') // Case 1: Zero prefix, e.g. chic1 or quack
    		break;

        if (*source >= '1' && *source <= '9') { 
        // Case 2: Prefix beginning with a number (usu 1-9)
        	if (*(source+1) != '_') {
        	// Case 2.1: Prefix containing zero '_', e.g. 1ablution
        		source += 1;
        		break;
        	}
        	else if (*(source+3) != '_') { // Case 2.2: Prefix containng one '_' e.g. 2_truce
        		
				source += 2;
        		break;
        	}
        	else { // Case 2.3: Prefix containing two '_', e.g. 1_i_feed2
        	
        		source += 4;
        		break;	
        	}
        }
        if((*source == 'i' || *source == 't') && *(source+1) == '_') { 
        // Case 3: Prefix beginning with 'i' or 't', e.g. i_sell or t_meet
            source += 2;
            break;
        }
        source++;
    }
    if (*source == '\0') {
    	fputs("Invalid title encountered!\n", stderr);
    	exit(1);
    }
    while (*source) {
    // Then cut off the tail
    	if (*source >= '1' && *source <= '9') // Case 1: Suffix beginning with a number
    		break;
    	if (*source == '_') // Case 2: Suffix beginning with a '_'
    		break;
	if(*source == '.') {
		break;
	}
    	*dest = *source;
    	source++;
    	dest++;
    }
    *++dest = '\0';
}

unsigned getNumberOfWordsInExample(const char * ex) {
	unsigned count;

	count = 0;
	while (*ex) {
		if (*ex == ' ')
			count++;
		ex++;
	}

	return count;
}

void fillWordArrayWithWordsInExample (const char * ex, char ** wordArray) {
	char * pWord;
	bool endOfWord = true;
	int i = 0;

	while (*ex) {
		if (endOfWord)
			pWord = wordArray[i]; // assign the next word to pWord
		*pWord = *ex;
		endOfWord = false;
		if (*ex == ' ') {
			i++; // move to next array in words
			*pWord = '\0'; // make a word a string
			endOfWord = true; // end of a word reached
		}
		ex++;
		pWord++;
	}
}

unsigned getLevenshteinDistance (const char * s, const char * t) {
	// TODO
	unsigned i, j;
	unsigned m, n; // m is length of t, n is length of s
	unsigned * matrix;
	char s_i, t_j; // s_i is ith character in str1 and t_j is jth character in str2
	unsigned cost;
	unsigned result; // resulting Levenshtein Distance
	unsigned cell;	// target value, the minimum of above, left and diagonal left
	unsigned above; // value above
	unsigned left; // value on the left
	unsigned diag; // value at diagonal left

	n = strlen(s); // row
	m = strlen(t); // column
	
	if (m == 0)
		result = n;
	if (n == 0)
		result = m;
	matrix = (unsigned *) malloc(sizeof (unsigned) * (m+1) * (n+1));
	
	for (i = 0; i <= n; i++) { 
		setValueForElementInMatrix(matrix, i, 0, n, i); // set first row to 0-m
	} 
	for (j = 0; j <=m; j++)
		setValueForElementInMatrix(matrix, 0, j, n, j); // set first colum to 0-n

	for (i = 1; i <= n; i++) {
		s_i = s[i-1];
		for (j = 1; j <= m; j++) {
			t_j = t[j-1];
			if (s_i == t_j)
				cost = 0;
			else
				cost = 1;
			above = getElementInMatrix(matrix, i-1, j, n);
			left = getElementInMatrix(matrix, i, j-1, n);
			diag = getElementInMatrix(matrix, i-1, j-1, n);
			cell = minimumValue(above + 1, left + 1, diag + cost);
			setValueForElementInMatrix(matrix, i, j, n, cell);
		}
	}
	result = getElementInMatrix(matrix, n, m, n);
	
	free(matrix);
	matrix = NULL;

	return result;
}

unsigned minimumValue(unsigned x, unsigned y, unsigned z) {
	unsigned min;

	min = x;
	if (y < min)
		min = y;
	if (z < min)
		min = z;
	return min;
}

void setValueForElementInMatrix(unsigned * pOrigin, unsigned col, unsigned row, unsigned nCols, unsigned x) {
	unsigned * pItem;

	pItem = getPointerToValueInMatrix(pOrigin, col, row, nCols);
	* pItem = x;
	
}

unsigned * getPointerToValueInMatrix(unsigned * pOrigin, unsigned col, unsigned row, unsigned nCols) {
	return pOrigin + col + (row * (nCols + 1));
}

unsigned getElementInMatrix(unsigned * pOrigin, unsigned col, unsigned row, unsigned nCols) {
	unsigned * pItem;

	pItem = getPointerToValueInMatrix(pOrigin, col, row, nCols);

	return *pItem;
}

const char * findWordInExample(const char * entryWd, const char ** wds, const unsigned n) {
	
	int i;

	unsigned * levenshteinDistances = (unsigned *) malloc(sizeof (unsigned) * n);
	unsigned minLevenshteinDistance;

	for (i = 0; i < n; i++) {
		levenshteinDistances[i] = getLevenshteinDistance(entryWd, (const char*)wds[i]);		
	}
	minLevenshteinDistance = 0;
	for (i = 1; i < n; i++)
		if (levenshteinDistances[minLevenshteinDistance] > levenshteinDistances[i])
			minLevenshteinDistance = i;

	free(levenshteinDistances);
	levenshteinDistances = NULL;
	return wds[minLevenshteinDistance];
}

bool exampleAssembler (const char * ex, const char * wordInExample, unsigned entryOrColloc, char assembledExample[]) {
	char * entryWordSpanHead = "<span class=emph>";
	char * collocationSpanHead = "<span class=colloc>";
	char * spanEnd = "</span>";
	char * ptrToWordInExample;
	char partBeforeWordInExample[LEN];
	const char * partAfterWordInExample;
	
	if (entryOrColloc == 1){
		ptrToWordInExample = strstr(ex, wordInExample);
		if (*ex == '\0')
			puts("Empty example string encountred!");
	}
	else if (entryOrColloc == 0) {
		if (*ex == '\0')
			puts("Empty example string encountred!");
		ptrToWordInExample = findPtrToWordInExample(ex, wordInExample);
	}
	else {
		puts("Invalid entryOrColloc parameter!");
		return false;
	}

	if (ptrToWordInExample == NULL) {
		puts("Can't find ptrToWordInExample in exampleAssembler!");
		return false;
	}

	getPartBeforeWord(ex, ptrToWordInExample, partBeforeWordInExample);
	if (entryOrColloc == 1)
		strcat(partBeforeWordInExample, entryWordSpanHead);
	else
		strcat(partBeforeWordInExample, collocationSpanHead);
	
	strcat(partBeforeWordInExample, wordInExample);
	strcat(partBeforeWordInExample, spanEnd);
	partAfterWordInExample = getPartAfterWordInExample(ptrToWordInExample, wordInExample);
	strcat(partBeforeWordInExample, partAfterWordInExample);
	strcpy(assembledExample, partBeforeWordInExample);

	return true;
}

void getPartBeforeWord (const char * ex, const char * ptr2WdInEx, char savePartBeforeWord[]) {
	
	while (ex != ptr2WdInEx) {
		*savePartBeforeWord = *ex;
		ex++;
		savePartBeforeWord++;
	}
	*savePartBeforeWord = '\0';
}

const char * getPartAfterWordInExample(const char * ptr2WdInEx, const char * WdInEx) {
	unsigned length = strlen(WdInEx);
	unsigned i = 0;

	while (*WdInEx) {
		if (*ptr2WdInEx == *WdInEx)
			i++;
			
		ptr2WdInEx++;
		WdInEx++;
		if (i == length)
			break;
	}
	return ptr2WdInEx;
}

void freeMem(char ** ptr2Mem, unsigned num) {
	int i;

	for (i = 0; i < num; i++) {
		free(ptr2Mem[i]);	
	}
	free(ptr2Mem);
	ptr2Mem = NULL;
}

char * findPtrToWordInExample(const char * ex, const char * wordInExample) {
	char * partAfterSpanEnd;
	unsigned cnt = 0;
	
	while (*ex) {
		if (*ex == '>')
			cnt++;
		if (cnt == 2)
			break;
		ex++;
	}
	partAfterSpanEnd = strstr(ex, wordInExample);

	return partAfterSpanEnd;
}

bool writeToHTMFile(const char * assembledEx, const char * htmFileName) {
	FILE * in, * out;
	char ch;
	bool lessThanFound = false, pFound = false, greaterThanFound = false, eFound = false, dot1Found = false, gFound = false, dot2Found = false, slashFound = false, sFound = false, cFound = false, rFound = false, iFound = false, tFound = false;
	unsigned count = 0;
		// ltf = less than (<) found, p ... > ... e... . ... g ... . ... the same
	
	if ((in = fopen(htmFileName, "r")) == NULL) {
		fprintf(stderr, "Error read %s!\n", htmFileName);
		return false;
	}
	if ((out = fopen("temp3.htm", "w")) == NULL) {
		fprintf(stderr, "Error write %s!\n", "temp3.htm");
		return false;
	}
	while ((ch = getc(in)) != EOF) { // htm file is not in double-byte (the char + 0x combo format)
		if (ch == '<'){
			putc(ch, out);		// no need to skip the 0x0 byte
			if (!lessThanFound) {
				count++;
				lessThanFound = true;
			}
			if ((ch = getc(in)) == 'p'){
				putc(ch, out);
				if (!pFound) {
					count++;
					pFound = true;
				}
				if ((ch = getc(in)) == '>'){
					putc(ch, out);
					if (!greaterThanFound) {
						count++;
						greaterThanFound = true;
					}
					if ((ch = getc(in)) == 'e'){
						putc(ch, out);
						if (!eFound) {
							count++;
							eFound = true;
						}
						if ((ch = getc(in)) == '.') {
							putc(ch, out);
							if (!dot1Found) {
								count++;
								dot1Found = true;
							}
							if ((ch = getc(in)) == 'g') {
								putc(ch, out);
								if (!gFound) {
									count++;
									gFound = true;
								}
								if ((ch = getc(in)) == '.') {
									putc(ch, out);
									if (!dot2Found) {
										count++;
										dot2Found = true;
									}
								}
							}
						}
					}
				}
			}
		}
		if (count == 7) {
			break;
		}
		putc(ch, out);
	}
	ch = getc(in);
	putc(ch, out); // get the space ' ' after e.g. and put it in output file
	while(*assembledEx) {
		putc(*assembledEx,out);
		assembledEx++;
	}
	lessThanFound = false;
	pFound = false;
	greaterThanFound = false;
	count = 0;
	while ((ch = getc(in)) != EOF) {
		if (ch == '<') {
			putc(ch, out);
			if (!lessThanFound) {
				count++;
				lessThanFound = true;
			}		
			if ((ch = getc(in)) == '/') {
			 putc(ch, out);
				if (!slashFound) {
					count++;
					slashFound = true;
				}
				if ((ch = getc(in)) == 's') {
					putc(ch, out);
					if (!sFound) {
						count++;
						sFound = true;
					}
					if ((ch = getc(in)) == 'c') {
						putc(ch, out);
						if (!cFound) {
							count++;
							cFound = true;
						}
						if ((ch = getc(in)) == 'r') {
							putc(ch, out);
							if (!rFound) {
								count++;
								rFound = true;
							}
							if ((ch = getc(in)) == 'i') {
								putc(ch, out);
								if (!iFound) {
									count++;
									iFound = true;
								}
								if ((ch = getc(in)) == 'p') {
									putc(ch, out);
									if (!pFound) {
										count++;
										pFound = true;
									}
									if ((ch = getc(in)) == 't') {
										putc(ch, out);
										if (!tFound) {
											count++;
											tFound = true;
										}
										if ((ch = getc(in)) == '>') {
											putc(ch, out);
											if(!greaterThanFound) {
												count++;
												lessThanFound = true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (count == 9) 
			break;
		putc(ch,out);
	}
	fclose(in);
	fclose(out);

	return true;
}
