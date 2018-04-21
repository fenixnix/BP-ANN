#ifndef NANNBP_H
#define NANNBP_H

#include "nlayer.h"

class NANNBP
{
public:
    NANNBP();
    void Init(int iLayerNum, int hLayerNum, int oLayerNum);
    vector<float> Run(vector<float> inputs);
    void Learn(vector<float> input, vector<float> output);

    void Print();

private:
    NLayer hLayer;
    NLayer oLayer;
};

#endif // NANNBP_H
