#include <stdio.h>

int f(int i);

int main(){
	printf("%d\n",f(15));
	return 0;
}


int f(int i)
{
   //int i = 0;
   int sum = 0;
   while(i>0)
      sum += i--;
   return sum;
}