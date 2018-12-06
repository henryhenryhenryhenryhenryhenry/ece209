#include <stdio.h>
int main(void){
	char last = 'c';
	char i='a';
	char j='a';
	while(i<=last){
		while(j<=last){
			printf("%c",i);
			printf("%c\n",j);
			j++;
		}
	j='a';
	i++;
	}
}
