#include <stdio.h>
#ifndef SECRET_TESTS
double M1=-1.0, B1=0; // Road 1 slope and intercept
double M2=1.0, B2=0;  // Road 2 slope and intercept
#else 
double M1=SECRET_M1, B1=SECRET_B1;
double M2=SECRET_M2, B2=SECRET_B2;
#endif

double M1; // Road 1 slope
double B1; // Road 1 y-intercept
double M2; // Road 2 slope
double B2; // Road 2 y-intercept

int Road=1, First_road=1;
int Changed_direction=0;
int Changed_road=0;
double Total_distance=0;
double Peak_speed=0.0; 
/* Function Declarations */
void track(double x, double y, double time);

int main() {

  double time, x, y;
  int ret;

  do {
    // get time,x,y coordinate from stdin
    ret = scanf("%lf%lf%lf",&time,&x,&y);
    
    if (ret==3)
      {
	    // call into the tracking algorithm
	    track(x,y,time);
      }

    // if we didn't get three doubles, time to quit
  } while(ret==3);

  // print out final results
  printf("Total distance = %.2lf\n",Total_distance);
  printf("Peak speed = %.2lf\n",Peak_speed);
  printf("# of changes in direction = %d\n",Changed_direction);
  printf("# of changes in road = %d\n",Changed_road);
  printf("First Road = %d, Last Road = %d\n",First_road,Road);
  
  return 0;
}
