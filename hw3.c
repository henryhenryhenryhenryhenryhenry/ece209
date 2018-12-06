#include <stdio.h>
int main(){
	int X =0;
	int Y =0;
	int W =0;
	int Z =0;
	int val = 0;
	printf("X Y W Z | !((!X&&!Y)^(W|Z))\n");
	for(X=0;X<=1;X++){
		for(Y=0;Y<=1;Y++){
			for(W=0;W<=1;W++){
				for(Z=0;Z<=1;Z++){
					val= !((!X && !Y) ^ (W | Z));
					printf("%d %d %d %d | %d\n",X,Y,W,Z,val);
				}
			}
		}
	}
	
	
	
	return 0;
}