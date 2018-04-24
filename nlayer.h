#ifndef NLAYER_H
#define NLAYER_H

#include "nnerve.h"

class NLayer
{
public:
    NLayer();
    NLayer(int nCnt, int wtCnt);
    void RndInit(int nCnt,int wtCnt);
    vector<float> Run(vector<float> inputs);
    vector<float> LearnOutput(vector<float> inputs, vector<float> outputs);
    vector<float> Learn(vector<float> inputs, vector<float> errors);
    string Print();

    vector<float> GetBPErrs(vector<float> errs);

private:
    vector<NNerve> nnerves;
    int wtCnt = 0;
};

#endif // NLAYER_H
