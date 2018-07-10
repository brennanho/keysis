#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define NUMBER '0' 
#define MAXOP 100
#define BUFSIZE 100
#define MAXVAL 100
char buf[BUFSIZE];
char s[MAXOP];
double val[MAXVAL];
int bufp = 0;          
int sp = 0;         

double pop() {
   if (sp > 0) 
      return val[--sp];
   else 
      printf("Could not retrieve data, s is empty.\n");
   return 0;
}

void push(double data) {

   if(sp < MAXVAL)  
      val[sp++] = data;
   else 
      printf("Could not insert data, s is full.\n");
   
}

int getch(void) 
{
   return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
   if (bufp >= BUFSIZE)
      printf("ungetch: too many characters\n");
   else
      buf[bufp++] = c;
}

//From http://www.learntosolveit.com/cprogramming/Ex_4.3_rpn_modulus_negative.html
int getop(char s[])
{
    int i,c;

    while((s[0] = c = getch()) == ' ' || c =='\t')
        ;
    s[1] = '\0';
    
    i = 0;
    if(!isdigit(c) && c!='.' && c!='-')
        return c;

    if(c=='-')
        if(isdigit(c=getch()) || c == '.')
            s[++i]=c;
        else
        {
            if(c!=EOF)
                ungetch(c);
            return '-';
        }
    
    if(isdigit(c))
        while(isdigit(s[++i] =c =getch()))
            ;

    if(c=='.')
        while(isdigit(s[++i] = c=getch()))
            ;
    
    s[i] = '\0';
    if(c != EOF)
        ungetch(c);
    return NUMBER;
}

void polishCalc()
{
   int type;
   double op2;
   while ((type = getop(s)) != EOF)
   {
      switch (type) 
      {
         case 't': //Print top element
            printf("Top element: %f\n", val[sp]);
            break;
         case 'd': //Duplicate top element?
            push(val[sp]);
            break;
         case 's': //swap top 2 elements
            printf("s\n");
            op2 = pop();
            double op1 = pop();
            push(op2);
            push(op1);
            break;
         case NUMBER:
         printf("num\n");
            push(atof(s));
            break;
         case '+':
            printf("+\n");
            push(pop() + pop());
            break;
         case '-':
            printf("-\n");
            op2 = pop();
            push(pop() - op2);
            break;
         case '*':
            printf("s\n");
            push(pop() * pop());
            break;
         case '/':
            op2 = pop();
            if (op2 != 0.0)
               push(pop() / op2);
            else
               printf("error: zero divisor\n");
            break;
         case '%':
            op2 = pop();
            if (op2 != 0.0)
               push(fmod(pop(), op2));
            else
               printf("error: cannot mod 0\n");
            break;
         case '\n':
            printf("\t%.8g\n", pop());
            break;
         default:
            printf("error: unknown command %s\n", s);
            break;
      }
   }
}

int main(void)
{
   polishCalc();
   
   printf("%s\n",s);
   return 0;
}