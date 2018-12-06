/* Henry Lindbo - ECE 209 sec 051
 * Program 2 - Tracker.c
 *  this program takes raw "gps" iputs (x coord, y coord, and time delta) along with
 * 	two predifined roads (y=mx+b form) and prints various statistics about the path taken
 * 
 *  either EOS linux or Virtual Box is fine for grading
 *   remember to use -lm when compiling on linux machine since the math library is used
 */

#include <stdio.h>
#include <math.h>

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
double get_y(double x, int road);
double x_intercept(void);
double distance(double x1, double y1, double x2, double y2);
double nearest_point_on_road(double x, double y, int road);
int closest_road(double x, double y, int road);
double intercept();


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

void track(double x, double y, double time) {
	static int count=0; // global variable 
	static double prior_x; // global variable	 
	static double prior_delta; // another global var
	
	double newDist;
	
	if(count==0){
		Road = closest_road(x,y,1);
		First_road = Road;
		prior_x = nearest_point_on_road(x,y,Road);
	}else if(count>0){
		if(Road == closest_road(x,y,Road)){// case for if road does not change
			Road = closest_road(x,y,Road);
			newDist = distance( nearest_point_on_road(x,y,Road),
								get_y(nearest_point_on_road(x,y,Road),Road),
								prior_x,
								get_y(prior_x,Road)
								);//get distance
			Total_distance += newDist;
			
			if(count>1){
				if((x-prior_x < 0 && prior_delta > 0) || (x-prior_x > 0 && prior_delta < 0)){//check if direction has changed along the same road
					Changed_direction++;
				}
			}
		}else{//case for if road has changed
			Road = closest_road(x,y,Road);
			newDist = distance( nearest_point_on_road(x,y,Road),
								get_y(nearest_point_on_road(x,y,Road),Road),
								intercept(),
								get_y(intercept(),Road))
					+ distance( intercept(),
								get_y(intercept(),Road),
								prior_x,
								get_y(prior_x,Road));// add distance from old point to intersection and distance from intersection to new point
			Total_distance += newDist;
			Changed_direction++;
			Changed_road++;
		}
		
		if(newDist/time > Peak_speed){//update max speed
			Peak_speed = newDist/time;
		}
		
		
		prior_delta = x-prior_x;//update prior delta for next direction check
		prior_x = nearest_point_on_road(x,y,Road);//update prior x for next position check
	}
	
	count++;// increment number of times track has run
}


double distance(double x1, double y1, double x2, double y2){//takes in 2 xy coords, returns distance via pieThugOrigin theorem
	return (sqrt((pow((x2-x1),2))+(pow((y2-y1),2))));
}

double get_y(double x, int road){//gets y part of xy coord given x and road the point is on
	if(road==1){
		return M1*x+B1;
	}else if(road==2){
		return M2*x+B2;
	}
}

double intercept(){
	return (B2-B1)/(M1-M2);
}

double nearest_point_on_road(double x, double y, int road){//given xy coord and a road, returns closest xy coord on given road via algebra
	double b;
	if(road==1){
		b = y - x*(-1/M1);
		return (b - B1)/(M1-(-1/M1)); //algebra
	}else if(road==2){
		b = y - x*(-1/M2);
		return (b - B2)/(M2-(-1/M2)); //more algebra
	}
}

int closest_road(double x, double y, int road){//given xy coord and a road, returns which road is actually closer to xy coord
	if( distance(x,y,nearest_point_on_road(x, y, road),get_y(nearest_point_on_road(x, y, road),road))<.0001){
		return road;// if distance to given road <.0001 return given road
	}else if(distance(x,y,nearest_point_on_road(x, y, 1),get_y(nearest_point_on_road(x, y, 1),1))-distance(x,y,nearest_point_on_road(x, y, 2),get_y(nearest_point_on_road(x, y, 2),2))<.0001 &&
				distance(x,y,nearest_point_on_road(x, y, 1),get_y(nearest_point_on_road(x, y, 1),1))-distance(x,y,nearest_point_on_road(x, y, 2),get_y(nearest_point_on_road(x, y, 2),2))>-.0001){
		return road;// if distances are the same return given road
	}else if(distance(x,y,nearest_point_on_road(x, y, 1),get_y(nearest_point_on_road(x, y, 1),1))>distance(x,y,nearest_point_on_road(x, y, 2),get_y(nearest_point_on_road(x, y, 2),2))){
		return 2;// if closer to road 2 return road 2
	}else if(distance(x,y,nearest_point_on_road(x, y, 1),get_y(nearest_point_on_road(x, y, 1),1))<distance(x,y,nearest_point_on_road(x, y, 2),get_y(nearest_point_on_road(x, y, 2),2))){
		return 1;// if closer to road 1 return road 1
	}
}






