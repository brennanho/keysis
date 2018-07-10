#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>

//2.01
void getRanges(void) 
{
	printf("char min: %d, char max: %d\n", CHAR_MIN, CHAR_MAX);
	printf("int min: %d, int max: %d\n", INT_MIN, INT_MAX);
	printf("short min: %d, short max: %d\n", SHRT_MIN, SHRT_MAX);
	printf("long min: %ld, long max: %ld\n", LONG_MIN, LONG_MAX);
	printf("float min: %.10f, float max: %.10f", FLT_MIN, FLT_MAX);

	/* For long using computation :
		signed : [-(2^(N-1)),2^(N-1) -1] unsigned: [0, 2^(N-1) + 2^(N-1) - 1]*/
	int bits = 8 * sizeof(long);
	unsigned long long unsignedMax = (1LLU << (bits - 1)) + ((1LL << (bits - 1)) - 1);
	printf("long unsigned: [0, %llu]\n", unsignedMax); 

	long long minSigned = -(1LL << (bits -1));
	long long maxSigned = (1LL << (bits - 1)) -1;
	printf("long signed: [%lld, %lld]\n", minSigned, maxSigned);


}

//2.02 Using nested conditions rather than && and !!
void forLoop(void) 
{
	char s[10];
	char c;
	int lim = 10;
	for (int i =0; i < lim-1; i++)
	{
		if ((c = getchar()) != '\n')
		{
			if (c != EOF)
				s[i] = c;
		}
	}
}

//2.03 Convert hex to decimal
int htoi(char* s)
{
	int num = 0;
	int lenS = strlen(s);
	for (int i = 0; i < lenS; i++) 
	{
		int temp = s[i];
		if (temp >= 48 && temp <= 57) // Digit
			temp = temp - 48; 
		else if (temp >= 65 && temp <= 70) //Uppercase letter
			temp = temp - 55;
		else if (temp >= 97 && temp <= 102) //Lowercase letter
			temp = temp - 87;
		num = num + temp*pow(16, lenS-i-1);
	}
	return num;
}

//2.4 Deletes any character from s that matches c
char* squeezeHelper(char* s, int c) 
{
	int i,j;
	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
	return s;
}

//Deletes all characters from s1 that match any character of s2
void squeeze(char* s1, char* s2)
{
	for (int i = 0; s2[i] != '\0'; i++)
	{
		s1 = squeezeHelper(s1, s2[i]);
	}
	printf("s1: %s", s1);
}

//2.05 Returns first location to where a character of s2 occurs in s1
int any(char* s1, char* s2) 
{
	int lens2 = strlen(s2);
	for (int i = 0; s1[i] != '\0'; i++)
	{
		s2 = squeezeHelper(s2, s1[i]); //Return the first removed character location from s1
		if (strlen(s2) < lens2) 
			return i;
	}
	return -1;
}

unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p + 1 - n) & ~(~0 << n));
}

//2.06
unsigned setbits(unsigned x, int p, int n, unsigned y) 
{
	int numBitsY = (int)(floor(log(y) / log(2)) + 1);
	unsigned yBits = getbits(y, p, numBitsY);

	return x;
}

// From http://www.learntosolveit.com/cprogramming/Ex_2.6_setbits.html
// unsigned setbits(unsigned x,int p,int n,unsigned y)
// {
//     return x & ~(~(~0 << n) << (p+1-n)) | ( y & ~(~0<<n)) << (p+1-n);
// }

//2.07 - invert bits (get bits from p to n, then or with the flipped bits)
unsigned invert(unsigned x, int p, int n) 
{
	unsigned xRes = getbits(x, p, n);
	x = x | ~xRes;
	return x;
}

//2.08 - rotate bits
unsigned rightrot(unsigned x, int n)
{
	int nBits = 8 * sizeof(x);
	unsigned rbit; = x << (nBits - n);

	x = x >> n;
	x = x | rbit;
	return x;

}

//2.09 - Count number of set bits
int bitCount(unsigned x)
{
	int b = 0;
	while (x != 0)
	{
		x &= (x - 1);
		b++;
	}
	return b;
}

//2.10
char lower(char s)
{
	if (s >= 'A' && s <= 'Z')
		return s + 32;
	else
		return s;
}

int main(void)
{	
	//printf("%d\n",setbits(4,1,1,1));
	unsigned int res = invert(15,4,5);
	printf("%u\n",res);
	printf("%d\n", rightrot(12,2));

	//getRanges();

	// printf("%d\n", getbits(15,3,4)); // bit[3] = {0,1,2,3}

	// char s[] = "7DE";
	// printf("%d\n", htoi(s));

	// char s1[] = "hellho";
	// char s2[] = "h";
	// //squeeze(s1,s2);
	
	// printf("any index: %d\n", any(s1,s2));
	//printf("bitCount: %d\n", bitCount(11));
}	