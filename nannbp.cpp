#include "nannbp.h"

NAnnBp::NAnnBp()
{

}

void NAnnBp::Init(int iLayerNum, int hLayerNum, int oLayerNum)
{
    hLayer.RndInit(hLayerNum,iLayerNum);
    oLayer.RndInit(oLayerNum,hLayerNum);
}

vector<float> NAnnBp::Run(vector<float> inputs)
{
    return oLayer.Run(hLayer.Run(inputs));
}

void NAnnBp::Learn(vector<float> input, vector<float> output)
{
    auto bp = oLayer.LearnOutput(hLayer.Run(input),output);
    hLayer.Learn(input,bp);
}

void NAnnBp::Print()
{
    hLayer.Print();
    oLayer.Print();
}
