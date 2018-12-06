#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <direct.h>

int width = 16;
int height = 32;
int delayval = 3e8;
int generations;

//int Old[width][height]
/*{ {0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,1,1,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0} };*/
//int New[width][height];

int Old[16][32];
int New[16][32];

void clear();
void print();
int chkResetNeeded();
void reset();
int imod(int x);
int jmod(int x);
int countNeighbors(int i,int j);
void nextState();
void delay(unsigned int secs);

int main (void){
	generations = 0;
	srand(time(NULL));
	reset();
	while(1){
		//clear();
		print();
		generations++;
		nextState();
		int i,j;
		for(i=0;i<width;i++){
			for(j=0;j<height;j++){
				Old[i][j]=New[i][j];//copy new into old
			}
		}
		if (chkResetNeeded()){
			reset();
		}
		delay(delayval);
	}
}

void delay(unsigned int secs){//find a better way to do this!
	int i;
	for(i=0; i<secs; i++);
}

void clear(){
	int i, j;
	for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			Old[i][j]=0;
		}
	}
}

void print(){
	printf("\n");
	int i, j;
	for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			if(New[i][j] >= 1)
				printf("@");
			else
				printf(".");
		}
		printf("\n");
	}
	printf("\n");
	printf("-- generations: %d --\n",generations);
}

int chkResetNeeded(){//checks if any cell is too old or if all cells are dead
  int numDead=0;
  int oldest=0;
  int i,j;
  for(i=0;i<width;i++){
    for(j=0;j<height;j++){
      if(New[i][j]>oldest)
        oldest = New[i][j];
      if(New[i][j]==0)
        numDead++;
    }
  }
  if(oldest>(height*width) && numDead>(.75*height*width)){
    return 1;
  }else if(numDead>=height*width){
	clear();
	print();
    delay(delayval);//display the blank board for a little bit
  }else{
    return 0;
  }
}

void reset(){//resets board to new psuedo random state
	int i, j;
	for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			Old[i][j]=rand()%2;
		}
	}
}

int imod(int x){//returns to mod of a number, useful to implement overlap
	return (x+width)%width;
}

int jmod(int x){//returns to mod of a number, useful to implement overlap
	return (x+height)%height;
}

int countNeighbors(int i,int j){//counts the number of neighbors for a given cell
	int neighbors=0;
	if(Old[imod(i+1)][jmod(j)]>=1)
		neighbors++;
	if(Old[imod(i-1)][jmod(j)]>=1)
		neighbors++;
	if(Old[imod(i)][jmod(j+1)]>=1)
		neighbors++;
	if(Old[imod(i)][jmod(j-1)]>=1)
		neighbors++;
	if(Old[imod(i+1)][jmod(j+1)]>=1)
		neighbors++;
	if(Old[imod(i-1)][jmod(j-1)]>=1)
		neighbors++;
	if(Old[imod(i-1)][jmod(j+1)]>=1)
		neighbors++;
	if(Old[imod(i+1)][jmod(j-1)]>=1)
		neighbors++;
	return neighbors;
}

void nextState(){//calculates the next state
	int i,j;
	for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			int neighbors = countNeighbors(i,j);
			switch(neighbors){
				case 0: if(Old[i][j]>=1)
							New[i][j]=0;
						else if(Old[i][j]==0)
							New[i][j]=0;
						break;
				case 1: if(Old[i][j]>=1)
							New[i][j]=0;
						else if(Old[i][j]==0)
							New[i][j]=0;
						break;
				case 2: if(Old[i][j]>=1)
							New[i][j]++;
						else if(Old[i][j]==0)
							New[i][j]=0;
						break;
				case 3: if(Old[i][j]>=1)
							New[i][j]++;
						else if(Old[i][j]==0)
							New[i][j]++;
						break;
				case 4: if(Old[i][j]>=1)
							New[i][j]=0;
						else if(Old[i][j]==0)
							New[i][j]=0;
						break;
				default: New[i][j]=0;
						break;
			}
		}
	}
}