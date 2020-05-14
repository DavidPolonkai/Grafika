#include "utils.h"

#include <math.h>

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

double radian_to_degree(double radian){
	return radian * (1/(M_PI/180));

}
