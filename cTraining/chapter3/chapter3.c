#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//3.1
int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n;
	while (low < high)
	{
		mid = low + ((high - low)/2);
		if (v[mid] < x)
			low = mid + 1;
		else
			high = mid;
	}

	if (low < n && v[low] == x)
		return low;

	return -1;
}

//3.2
char* escape(char* s, char* t)
{
	for (int i = 0; s[i] != '\0'; i++)
	{	
		switch (s[i])
		{
			case '\t':
				strcat(t, "\\t");
			case '\n':
				strcat(t, "\\n");
			default:
				t[i] = s[i];
		}
	}
	return t;
}

//3.3 got from http://www.learntosolveit.com/cprogramming/Ex_3.3_expand.html
char* expand(char* s1, char* s2)
{

	int i,j,c;
	i = j = 0;
	for (c = s1[i]; c != '\0'; c = s1[i++])
	{
		if (s1[i] == '-' && s1[i+1] >= c)
		{
			i++;
			while (c < s1[i])
				s2[j++] = c++;
		}
		else
			s2[j++] = c;
	}
	s2[j] = '\0';
	printf("%s\n",s2);

}

//3.4
void reverse(char* s)
{
	char temp;
	for (int i = 0; i < strlen(s)/2; i++)
	{
		temp = s[i];
		s[i] = s[strlen(s) - 1 - i];
		s[strlen(s) - 1 - i] = temp;
	}
}

//Since the - sign takes an extra character, it would need an extra byte of space in s
void itoa(int n, char s[])
{
	int i, sign;
	i = 0;
	if ((sign = n) < 0) //absolute value {
		n = -n;
	s[i++] = n % 10 + '0';
	while ((n /= 10) > 0)
	{
		s[i++] = n % 10 + '0';
	}
	//Create new array with one byte more
	char s2[strlen(s) + 1];
	strcpy(s2, s);
	if (sign < 0) 
		s2[i++] = '-';
	s2[i] = '\0';
	reverse(s2);
	printf("%s\n", s2);
}

//3.5 - convert integer to a number with base b
void itob(int n, char s[], unsigned b)
{
	int sign;
	if (n < 0) {
		sign = -1;
		n *= -1;
	}

	int i = 0;
	while (n > 0)
	{
		if (n % b < 10)
			s[i++] = (n % b) + '0'; // digits 0..9
		else
			s[i++] = (n % b) + '7'; // characters A..F
		n /= b;
	}

	if (sign == -1)
		s[i] = '-';

	reverse(s);
	printf("%s\n",s);

}

//3.6 itoa with padding on left
void itoapad(int n, char s[], int w)
{
	int i, sign;
	i = 0;
	if ((sign = n) < 0) //absolute value {
		n = -n;
	s[i++] = n % 10 + '0';
	while ((n /= 10) > 0)
	{
		s[i++] = n % 10 + '0';
	}
	//Create new array with one byte more
	char s2[strlen(s) + 1];
	strcpy(s2, s);
	if (sign < 0) 
		s2[i++] = '-';

	while (i < w) // padding step
		s[i++] = ' ';

	s2[i] = '\0';
	reverse(s2);
	printf("%s\n", s2);
}

int main(void)
{
	// int a[10] = {1,2,3,4,5,6,7,8,9,10};
	// printf("%d\n",binsearch(4,a,10));

	// char s[50] = "high how	are you";
	// char* t = malloc(50*sizeof(char));
	// t = escape(s,t);
	// printf("%s",t);

	//char s[100];
	//itoapad(-1, s,10);

	//char s2[50];
	//itob(16, s2, 16);
	
	char s1[10] = "a-z";
	char s2[100];
	expand(s1,s2);

	return 0;
}