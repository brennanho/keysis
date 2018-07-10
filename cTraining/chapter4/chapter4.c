#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//4.01
int strrindex(char* s, char t)
{
	int lenS = strlen(s);
	for (int i = lenS-1; i >= 0; i--)
	{
		if (s[i] == t)
			return i;
	}

	return -1;
}

//4.02
double atof(char s[])
{
	double val, power, valExp, valPower;
	int i, sign, signExp;
	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++) 
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E') // If scientific notation
	{
		i++;
		if (s[i] == '-')
		{
			signExp = -1;
			i++;
		}
		else
			signExp = 1;

		valPower = 0.0;
		while (s[i] != '\0') 
		{
			printf("%c\n",s[i]);
			valPower = valPower * 10 + (s[i] - '0');
			i++;
		}
		printf("signExp = %d, valPower = %f", signExp, valPower);
		return (sign * val / power) * pow(10, signExp*valPower);
	}
	else // Regular notation
		return sign * val / power;
}

//Helper function
char* reverse(char* s)
{
	char temp;
	for (int i = 0; i < strlen(s)/2; i++)
	{
		temp = s[i];
		s[i] = s[strlen(s) - 1 - i];
		s[strlen(s) - 1 - i] = temp;
	}
	return s;
}

//4.12
char* printd(int n, char* a, int start)
{
	if (n <= 0)
		return reverse(a);
	else
	{
		a[start++] = n % 10 + '0';
		n /= 10;
		return printd(n, a, start);
	}
}

//4.13 - Recursive version of reversing a string
char* rReverse(char* s, int start, int end)
{
	if (start >= end)
		return s;
	else
	{
		char temp = s[start];
		s[start] = s[end-1];
		s[end-1] = temp;
		return rReverse(s, start+1, end-1);
	}
}

// Macro for swapping to variable values
#define swap(t,x,y) do {t temp = x; x = y; y = temp;} while(0)

int main(void)
{
	//char str[20] = "Hi how are you?";
	//char t = 'x'; 
	//printf("pos: %d\n", strrindex(str,t));

	// char doub[10] = "123.45e3";
	// printf("double: %f\n", atof(doub));
	
	// char testR[5] = "hello";
	// rReverse(testR,0,5);
	// printf("%s\n",testR);

	// char testD[4];
	// int n = 354;
	// printf("%s\n",printd(3012,testD,0));

	int x = 5;
	int y = 3;
	swap(int,x,y);
	printf("x: %d, y: %d\n",x,y);

	return 0;
}


