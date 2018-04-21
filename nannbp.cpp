#include "nannbp.h"

NANNBP::NANNBP()
{

}

void NANNBP::Init(int iLayerNum, int hLayerNum, int oLayerNum)
{
    hLayer.RndInit(hLayerNum,iLayerNum);
    oLayer.RndInit(oLayerNum,hLayerNum);
}

vector<float> NANNBP::Run(vector<float> inputs)
{
    return oLayer.Run(hLayer.Run(inputs));
}

void NANNBP::Learn(vector<float> input, vector<float> output)
{
    auto bp = oLayer.LearnOutput(hLayer.Run(input),output);
    hLayer.Learn(input,bp);
}

void NANNBP::Print()
{
    hLayer.Print();
    oLayer.Print();
}
