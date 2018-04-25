#include "nannbp.h"

NAnnBp::NAnnBp()
{

}

void NAnnBp::Init(vector<int> layerNums)
{
  layers.clear();
  assert(layerNums.size()>2);
  for(int i = 0;i<layerNums.size()-1;i++){
      NLayer layer(layerNums[i+1],layerNums[i]);
      layers.push_back(layer);
    }
}

vector<float> NAnnBp::Run(vector<float> inputs)
{
  vector<float> result = inputs;
  for(int i = 0;i<layers.size();i++){
      result = (layers[i].Run(result));
    }
  return result;
}

vector<vector<float> > NAnnBp::RunGetAllLayerOutput(vector<float> inputs)
{
  vector<vector<float> > outputs;
  vector<float> result = inputs;
  for(int i = 0;i<layers.size();i++){
      result = (layers[i].Run(result));
      outputs.push_back(result);
    }
  return outputs;
}

void NAnnBp::Learn(vector<float> input, vector<float> output)
{
  auto outputs = RunGetAllLayerOutput(input);
  outputs.insert(outputs.begin(),input);
  auto bp = layers[layers.size()-1].LearnOutput(outputs[outputs.size()-2],output);
  for(int i = layers.size()-2; i>=0; i--){
      bp = layers[i].Learn(outputs[i],bp);
    }
}

string NAnnBp::Print()
{
  ostringstream os;
  for(int i = 0;i<layers.size();i++){
      os<<"L#"<<i<<":";
      os<<layers[i].Print();
    }
  return os.str();
}
