#ifndef ACTIVEFUNC_H
#define ACTIVEFUNC_H

#include <math.h>
using namespace std;

namespace ACTFUNC{
inline float Step(float in){
  return in<=0 ? 0:1;
}

inline float Sgn(float in){
  return in<0 ? -1:1;
}

inline float Liner(float in){
  return in;
}

inline float Ramp(float in){
  if(in<0){
      return 0;
    }
  if(in<=1){
      return in;
    }
  return 1;
}

inline float Sigmoid(float in){
  return 1.0f/(1.0f+exp(-in));
}

inline float Tanh(float in){
  return (exp(in) - exp(-in))/(exp(in) + exp(-in));
}
}

#endif // ACTIVEFUNC_H
