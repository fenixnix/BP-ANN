#include "nnerve.h"

NNerve::NNerve()
{

}

float NNerve::Run(vector<float> input)
{
  assert(input.size()==weights.size());
  float s = bias;
  for(int i = 0;i<input.size();i++){
      s += input[i]*weights[i];
    }
  return ACTFUNC::Sigmoid(s);
}

float NNerve::Learn(vector<float> input, float error)
{
  float O = Run(input);
  float E = O *(1.0f - O)*error;
  for(int i = 0;i<input.size();i++){
      weights[i] += lambda*E*input[i];
    }
  bias += lambda*E;
  return E;
}

float NNerve::LearnOutput(vector<float> input, float taget)
{
    float O = Run(input);
    return Learn(input,taget-O);
}

void NNerve::Init(float defVal, int cnt)
{
  weights.clear();
  for(int i = 0;i<cnt;i++){
      weights.push_back(defVal);
    }
}

void NNerve::RndInit(int cnt)
{
  for(int i = 0;i<cnt;i++){
      float val = (float)(rand()%2000-1000)/1000.0f;
      //cout<<val<<endl;
      weights.push_back(val);
      //weights.push_back(0.1f);
    }
  //bias = (float)(rand()%2000-1000)/1000.0f;
    bias = 0;
}

string NNerve::Print()
{
  ostringstream os;
  os<<"\tN Ct:"<<weights.size()<<" Bias:"<<bias<<endl;
  for(int i = 0;i<weights.size();i++){
    os<<"\t\t#"<<i<<":"<<weights[i]<<"|"<<endl;
  }
  return os.str();
}
