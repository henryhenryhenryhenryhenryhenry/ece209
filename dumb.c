#include <stdio.h>
int main(void){
	int v=-3;
	int w=2;
	int x=5;
	char z='1';
	printf("%d\n",+z);
	printf("%d\n",z);
	printf("%d\n",z+1);
	printf("%d\n",x+1&w-1);
	printf("%d\n",w++ -x);
	w=2;
	printf("%d\n",++ w);
	w=2;
	printf("%d\n",(~x)+1);
	x=5;
	printf("%d\n",w + ! + w);
	printf("%d\n",z<<x - 4);
	z='1';
	printf("%d\n",((v>>31)^v) - (v>>31) );
	v=-3;
	printf("%d\n", !!x);
	x=5;
	printf("%d\n", v >> 31^ v - v >> 31);
	v=-3;
	
	return 0;
}