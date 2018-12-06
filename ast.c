#include <stdio.h>
int main(void){
	int j;
	int i;
	int n = 10;
	for(i=1;i<=n;i++){
		for(j=1;j<=i;j++){
			printf("*");
	}
	printf("\n");
}
	return 0;
}