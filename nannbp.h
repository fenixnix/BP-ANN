#ifndef NANNBP_H
#define NANNBP_H

#include "nlayer.h"

class NAnnBp
{
public:
    NAnnBp();
    void Init(vector<int> layerNums);
    vector<float> Run(vector<float> inputs);
    vector<vector<float> > RunGetAllLayerOutput(vector<float> inputs);
    void Learn(vector<float> input, vector<float> output);

    string Print();

private:
    vector<NLayer> layers;
};

#endif // NANNBP_H
