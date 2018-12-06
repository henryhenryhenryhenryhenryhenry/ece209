#include <string.h>


typedef struct song Item;

struct song {
   char title[100];  /* a string less than 100 characters long */
   char album[100];
   char artist[100];
   int  year; /* any integer value */
   int playlist;
};

void sort(Item a[], int size, int key );
int less (Item* a, Item* b, int key);

int main(){
	
	return 0;
}


void sort(Item a[], int size, int key ){
	int i, j;
	Item t;
	int count=0;
	
	if (key!=1 && key!=2 && key!=0)
		return;
	
	for(i=0; i<size; i++){
		j = i;
		count=1;

		while(j>0 && less(&a[j],&a[j-1],key)>0) {// less means a[j]< a[j-1]
			count++;
			t=a[j];a[j]=a[j-1];a[j-1]=t;
			j--;
		}
	}
}
	
int less (Item* a, Item* b, int key){
	switch (key){
		case 0: return strcmp(a->artist,b->artist);// strcmp is >0 if a is first
		
		case 1: return strcmp(a->album,b->album);
		
		case 2: return b->year - a->year;
		
		default: return 0;
		
		
		
	}
	
}