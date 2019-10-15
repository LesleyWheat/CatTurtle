//General global functions

#include "arduino.h"
#include "miscFunctions.h"
/* generate a pair of normally distributed random numbers
* using a Box-Muller transformation. The mean is 0 -- numbers
* are equally likely to be + or -.  The required stdev is
* given in 'sigma'.  Either result pointers can be NULL, if
* you want just one number.
*/
double fuzzyNum(double num, double sigma){
  double
    sample,
     u1, u2,
     v1, v2, s,
     z1, z2;

  for (;;) {

     /* get two uniform random numbers from 0 to .999...
      */
     u1 = (float) random(RAND_MAX) / ((float) RAND_MAX + 1);
     u2 = (float) random(RAND_MAX) / ((float) RAND_MAX + 1);


     v1 = 2.0L*u1 - 1.0L;
     v2 = 2.0L*u2 - 1.0L;
     s = v1 * v1 + v2 * v2;

     if (s <= 1.0L && s != 0.0L)
        break;

  }

  z1 = sqrt (-2.0L * log(s) /  s) * v1;
  z2 = sqrt (-2.0L * log(s) / s) * v2;

  //if (r1 != NULL) *r1 = (z1*sigma);
  //if (r2 != NULL) *r2 = (z2*sigma);

  sample = (z1*sigma)+ num;
  
  return sample;
}

// Function that return average of an array. 

double averageArray(int a[], int n) { 
    // Find sum of array element 
    int sum = 0; 
    for (int i=0; i<n; i++) 
       sum += a[i]; 
  
    return sum/n; 
} 
