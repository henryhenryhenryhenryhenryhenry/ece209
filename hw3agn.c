#include <stdio.h>

void make_change(int amount, int quarters, int dimes, int nickels, int pennies);
int main(){
	make_change(99, 4, 4, 4, 4);
	return 0;
}

void make_change(int amount, int quarters, int dimes, int nickels, int pennies){
	if((25*quarters+10*dimes+5*nickels+pennies)<amount){
		printf("Not enough coins to make change");
		return;
	}
	while((25*quarters)>amount){
		quarters--;
	}
	amount-=quarters*25;
	if(quarters>0){
		printf("%d quarters ",quarters);
	}
	while((10*dimes)>amount){
		dimes--;
	}
	amount-=dimes*10;
	if(dimes>0){
		printf("%d dimes ",dimes);
	}
	while((5*nickels)>amount){
		nickels--;
	}
	amount-=nickels*5;
	if(nickels>0){
		printf("%d nickels ",nickels);
	}
	while((1*pennies)>amount){
		pennies--;
	}
	amount-=pennies;
	if(pennies>0){
		printf("%d pennies",pennies);
	}
	printf("\n");
	return;
	
	
}