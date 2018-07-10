#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Exercise 1/2 are hello world

/* pri~t Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300; floatinq-point version */

//Print heading above table
void exercise3(void) {
	float fahr, celsius;
	int lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	fahr = lower;
	printf("Fahrenheit to Celsius table \n");
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%3.0f %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}

//Celcius to Farenheit 
void exercise4(void) 
{
	float fahr, celsius;
	int lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	fahr = lower;
	printf("Celsius to Fahrenheit table \n");
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%6.1f %3.0f\n", celsius, fahr);
		fahr = fahr + step;
	}
}

//Reverse order print
void exercise5(void) 
{
	float fahr, celsius;
	int lower, upper, step;
	lower = 0;
	upper = 300;
	step = 20;
	fahr = upper;
	while (fahr >= lower) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%6.1f %3.0f\n", celsius, fahr);
		fahr = fahr - step;
	}
}

//Only returns 1 if 'ctr + d' entered
int exercise6(void) 
{
	return (getchar() != EOF); 
}

//Prints value of EOF
void exercise7(void) {
	printf("%d\n", EOF);
}

//Counts blanks, tabs, and lines in input
void exercise8(void) {
	int c, nTabs, nBlanks, nLines;
	nTabs = 0;
	nBlanks = 0;
	nLines = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
			nLines++;
		else if (c == '\t')
			nTabs++;
		else if (c == ' ')
			nBlanks++;
	}
	printf("tabs %d, lines %d, blanks %d\n", nTabs, nLines, nBlanks);
}

//remove trailing blanks/tabs
void exercise9(void) {
	int c, prev;
	prev = EOF;
	while ((c = getchar()) != EOF) 
	{
		if (c != ' ' || prev != ' ')
			printf("%c",c);
		prev = c;
	}
}

//Prints literal meaning for blanks, tabs, and backslash
void exercise10(void) {
	int c;
	while ((c = getchar()) != EOF) 
	{
		if (c == '\t')
			printf("\\t");
		else if (c == '\b')
			printf("\\b");
		else if (c == '\\')
			printf("\\");
		else
			printf("%c",c);
	}
}

//excersise 11... edge cases such as very long words (buffer overflow) or 1 character words
void exercise12(void) 
{
	int c;
	int prev = EOF;
	while ((c = getchar()) != EOF)
	{
		if ((c == ' ' || c == '\t') && prev != ' ')
			printf("\n");
		else if (c != ' ' || prev != ' ') 
			printf("%c",c);
		prev = c;
	}
}

//Horizontal histogram
void exercise13(void) 
{
	int c;
	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n')
			printf("\n");
		else
			printf("|");
	}
}

//Character frequency horizontal histogram
void exercise14(void)
{
	int c, i, nwhite, nother;
	nwhite = 0;
	nother = 0;
	int ndigit[10] = {0};
	
	while ((c = getchar()) != EOF)
	{
		if (c >= '0' && c <= '9')
			ndigit[c-'0']++;
		else if (c == ' ' || c == '\n' || c == '\t')
			++nwhite;
		else
			++nother;
	}

	//Print out the frequency for each digit
	for (int i = 0; i < 10; i++)
	{
		printf("%d: ",i);
		for (int j = 0; j < ndigit[i]; j++)
		{
			printf("|");
		}
		printf("\n");
	}

	printf("Whitespace: ");
	for (int i = 0; i < nwhite; i++)
		printf("|");
	printf("\nOther: ");
	for (int i = 0; i < nother; i++)
		printf("|");
	printf("\n");

}

// exercise 15/16 modifying existing code

//Print lines that are only >= 80
void exercise17(void)
{
	int wordMaxSize = 1000;
	char word[wordMaxSize];
	while (fgets(word, wordMaxSize, stdin) != NULL)
	{
		if (strlen(word) >= 80)
		{
			printf("%s",word);
			memset(word,'\0',wordMaxSize*sizeof(char));
		}	
	}
}

//Remove trailing blanks and tabs
void exercise18(void) 
{
	int c, prev;
	while ((c = getchar()) != EOF) 
	{
		if ((c != ' ' || prev != ' ') && (c != '\t' || prev != '\t'))
			printf("%c",c);
		prev = c;
	}
}

//Reverse a string in place
void reverse19(char* s)
{
	char temp;
	for (int i = 0; i < strlen(s)/2; i++)
	{
		temp = s[i];
		s[i] = s[strlen(s) - 1 - i];
		s[strlen(s) - 1 - i] = temp;
	}
}

// exercises 20-24 will take a long time...

// exercise 20 - Replaces tabs with appropriate number of tab spaces
char* detab(char* s, int tabSpaces)
{
	//Allocate new string with size accomadating added spaces
	int newStrLen = 0;
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '\t')
			newStrLen += tabSpaces;
		else
			newStrLen += 1;
	}
	char* newS = malloc(newStrLen * sizeof(char));

	int i = 0;
	int j = 0;
	int tabInd;
	while (i < newStrLen)
	{
		if (s[j] == '\t')
		{
			tabInd = 0;
			while (tabInd < tabSpaces)
			{
				newS[i++] = ' ';
				tabInd++;
			}
			j++;
		} 
		else
			newS[i++] = s[j++];

	}
	return newS;
}

//exercise 21 - Replaces spaces with minimum number of tabs + spaces combined
void entab(char* s, int tabSpace)
{
	int i = 0;
	int lenS = strlen(s);
	int numSpaces = 0;
	while (i < lenS)
	{
		if (s[i] == ' ')
			numSpaces++;

		else if (s[i] != ' ')
			numSpaces = 0;

		if (numSpaces >= tabSpace)
		{
			i -= tabSpace-1;
			lenS -= tabSpace-1;
			s[i] = '\t';

			//Shift string to the left by tabSpace-1 places
			for (int j = i+1; j < lenS; j++)
				s[j] = s[j+tabSpace-1];

			numSpaces = 0;
			s[lenS] = '\0';
		}
		i++;
	}
}

//exercise 22 - Fold lines
char* foldLines(char* s, int n)
{
	int i = 0;
	int j = 0;
	int foldInd = 0;
	int numRows = ceil(strlen(s) / n);
	int newSLen = numRows + strlen(s);
	char* newS = malloc(sizeof(char) * newSLen);

	while (i < newSLen)
	{
		if (foldInd >= n && (s[j] == ' ' || s[j] == '\t'))
		{
			newS[i] = '\n';
			foldInd = 0;
		}
		else
			newS[i] = s[j];

		i++;
		j++;
		foldInd++;
	}
	return newS;
}

//exercise 23 - Open a file (using current as sample) then write to a new file with same contents but comments removed
void removeComments(void)
{
	FILE* fr;
	FILE* fw;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fr = fopen("chapter1.c", "r");
    fw = fopen("chapter1R.c", "w");

   	int inComment = 0;
    while ((read = getline(&line, &len, fr)) != -1) 
    {
        int lenLine = strlen(line);
        char prev;
        int balancedQuotes = 0;
        for (int i = 0; i < lenLine; i++)
        {
        	if (line[i] == '"')
        		balancedQuotes++;

        	else if (line[i] == '/' && prev == '/' && (balancedQuotes % 2 == 0))
        	{
        		line[i] = ' ';
        		line[i-1] = ' ';
        	}

        	else if (prev == '/' && line[i] == '*')
        	{
        		line[i] = ' ';
        		line[i-1] = ' ';
        		inComment = 1;
        	}

        	else if (prev == '*' && line[i] == '/' && inComment == 1)
        	{
        		line[i] = ' ';
        		line[i-1] = ' ';
        		inComment = 0;
        	}

        	prev = line[i];
        }
        fprintf(fw, "%s", line);
    }

    fclose(fr);
    fclose(fw);
}

int main(void)
{
	//printf("%d",exercise6());
	// exercise3();
	// exercise4();
	// exercise5();
	// exercise6();
	// exercise7();
	// exercise8();
	// exercise10();
	// exercise12();
	//exercise13();
	//exercise14();
	//exercise16();
	//exercise18();

	// char s[] = "keysis";
	// reverse19(s);
	// printf("%s\n",s);

	// char s1[] = "hello	yo	hi";
	// char* newS = detab(s1, 5);
	// printf("%s\n",newS);
	// free(newS);

	// char s1[] = "hello       yo hi";
	// entab(s1, 3);
	// printf("%s\n",s1);

	// char s2[] = "hello yo world somethinggood hmm\n";
	// char* newS2 = foldLines(s2, 6);
	// printf("%s",newS2);
	// free(newS2);

	/*hey how are you 
	good wbu
	testing comments for remove comments
	heehehe*/

	removeComments();

	return 0;
}