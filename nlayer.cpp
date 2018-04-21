#include "nlayer.h"

NLayer::NLayer()
{

}

void NLayer::RndInit(int nCnt, int wtCnt)
{
    this->wtCnt = wtCnt;
    nnerves.clear();
    for(int i = 0;i<nCnt;i++){
        NNerve nerve;
        nerve.RndInit(wtCnt);
        nnerves.push_back(nerve);
    }
}

vector<float> NLayer::Run(vector<float> inputs)
{
    vector<float> output;
    int nerveCnt = nnerves.size();
    for(int i = 0;i<nerveCnt;i++){
        output.push_back(nnerves[i].Run(inputs));
    }
    return output;
}

vector<float> NLayer::GetBPErrs(vector<float> errs)
{
    auto nerveCnt = nnerves.size();
    vector<float> bpErrs;
    for(int i = 0;i<wtCnt;i++){
        float bpErrSum = 0;
        for(int j = 0;j<nerveCnt;j++){
            bpErrSum += errs[j]*nnerves[j].weights[i];
        }
        bpErrs.push_back(bpErrSum);
    }
    return bpErrs;
}

vector<float> NLayer::LearnOutput(vector<float> inputs, vector<float> outputs)
{
    vector<float> errs;
    auto nerveCnt = nnerves.size();
    for(int i = 0;i<nerveCnt;i++){
        errs.push_back(nnerves[i].LearnOutput(inputs,outputs[i]));
    }
    return GetBPErrs(errs);
}

vector<float> NLayer::Learn(vector<float> inputs, vector<float> errors)
{
    vector<float> errs;
    auto nerveCnt = nnerves.size();
    for(int i = 0;i<nerveCnt;i++){
        errs.push_back(nnerves[i].Learn(inputs,errors[i]));
    }
    return GetBPErrs(errs);
}

void NLayer::Print()
{
    auto nerveCnt = nnerves.size();
    for(int i = 0;i<nerveCnt;i++){
        nnerves[i].Print();
    }
    cout<<endl;
}
