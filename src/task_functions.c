#include "task_functions.h"

unsigned int get_random(unsigned int min, unsigned int max){
  int t;
  RDTSC(t);
  return (t%(max-min)+1)+min;
}
bool get_random_bool(){
  int t;
  RDTSC(t);
  return t%2;
}
