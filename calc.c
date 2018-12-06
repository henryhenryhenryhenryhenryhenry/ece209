#include <stdio.h>
#include <math.h>
/*
*   Henry Lindbo
*	program 1 for ece 209 - calc.c
*	this code makes a simple calculator
*	if on a linux machine -lm needs to be added to end of gcc command
*		because this code uses the math library
*
*
*/
int main(void){
	char command = ' ';
	double EARLIER = 0.0;
	double LATER = 0.0;
	int status = 0;
	double tmp = 0;
	while(command != 'q'){
		status = scanf("%lf",&tmp);
		if (status == 1 /* we got a double */) {
			// Take action if we get a double
			EARLIER = LATER;
			LATER = tmp;
		} else {
			// Call scanf again to get a command 
			if (EOF==scanf(" %c",&command)) {
				// You are at the end of file, set command=’q’ to force the program to quit
				command = 'q';
			} else {
				// You got a character
				// Figure out which command you received
				if ( command=='p' ) {
					// Execute code that implements print
					printf("%.3lf\n",EARLIER);
					printf("%.3lf\n",LATER);
				}else if ( command=='a'){//add
					LATER=LATER+EARLIER;
					printf("=%.3lf\n",LATER);
				}else if ( command=='s'){//subtract
					LATER=LATER-EARLIER;
					printf("=%.3lf\n",LATER);
				}else if ( command=='x'){//multiply
					LATER=LATER*EARLIER;
					printf("=%.3lf\n",LATER);
				}else if ( command=='d'){//divide
					if(EARLIER==0){//won't divide by 0
						printf("Divide by zero error.\n");
					}
					else{
						LATER=LATER/EARLIER;
						printf("=%.3lf\n",LATER);
					}
				}else if ( command=='^'){//exponent
					LATER=pow(LATER,EARLIER);
					printf("=%.3lf\n",LATER);
				}else if ( command=='w'){//swap later and earlier
					tmp=LATER;
					LATER=EARLIER;
					EARLIER=tmp;
				}else if ( command=='c'){//clear
					LATER=0;
					EARLIER=0;
				}else if ( command=='h'){//help dialog
					printf("----------command list-----------\n");
					printf("x : multiplies later by earlier\n");
					printf("d : divides later by earlier\n");
					printf("a : adds later to earlier\n");
					printf("s : subtracts earlier from later\n");
					printf("^ : raises later to earlier\n");
					printf("e : raises e by later");
					printf("w : swaps values of earlier and later\n");
					printf("c : clears earlier and later\n");
					printf("p : prints values of earlier and later\n");
					printf("h : prints this help message\n");
					printf("q : quits the program\n");
				}else if ( command=='*'){//not supported stuff
					printf("The operator * is not supported.\n");
				}else if ( command=='\x25'){//not supported stuff
					printf("The operator %% is not supported.\n");
				}else if ( command=='\\'){//not supported stuff
					printf("The operator \\ is not supported.\n");
				}else if ( command=='/'){//not supported stuff
					printf("The operator / is not supported.\n");
				}else if ( command=='e'){//e^later
					LATER=exp(LATER); //uses the math library to implement the exponential function
					printf("=%.3lf\n",LATER);
				}else if (command != 'q'){//not supported stuff
					printf("The operator %c is not supported.\n",command);
				}


		
			}
		}

		
	}
	printf("%.3lf\n",EARLIER);
	printf("%.3lf\n",LATER);
	
	
	
	
	
	return 0;
}