#include <stdio.h>
#include "number.h"

void printNumberValue(Number val){
    if(val.unionCase == 1){
        printf("%d", val.type._uint32);
    } else if(val.unionCase == 2){
        printf("%d", val.type._int);
    } else if(val.unionCase == 3){
        printf("%f", val.type._float);
    } else if(val.unionCase == 4){
        printf("%lf", val.type._double);
    } else {
        printf("Error: Invalid unionCase");
    }
}

void printNumberValueAndUcase(Number val){
    if(val.unionCase == 1){
      printf("val: %d - unionCase: %d (uint)", val.type._uint32, val.unionCase);
    } else if(val.unionCase == 2){
      printf("val: %d - unionCase: %d (int)", val.type._int, val.unionCase);
    } else if(val.unionCase == 3){
      printf("val: %f - unionCase: %d (float)", val.type._float, val.unionCase);
    } else if(val.unionCase == 4){
      printf("val: %lf - unionCase: %d (double)", val.type._double, val.unionCase);
    } else {
        printf("Error: Invalid unionCase: %d", val.unionCase);
    }
}