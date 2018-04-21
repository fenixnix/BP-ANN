#ifndef NNERVE_H
#define NNERVE_H

#include <vector>
#include <iostream>
#include <assert.h>
#include "activefunc.h"

using namespace std;

class NNerve
{
public:
  NNerve();
  float Run(vector<float> input);
  float Learn(vector<float> input, float error);
  float LearnOutput(vector<float> input, float taget);
  void Init(float defVal, int cnt);
  void RndInit(int wtCnt);

  void Print();

  vector<float> weights;
  float bias = 0;
  float lambda = 0.05f;
private:

};

#endif // NNERVE_H
