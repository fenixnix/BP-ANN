# BP-ANN
BP ANN Frameware by Nix

### NNerve
A nerve cell
You can use it to build an perceptron to solve AND OR problem but not XOR

### NLayer
A ANN layer consist of NNerve

### NAnnBp
A BP-ANN consist of NLayer
You can use it to build an multilayer ANN to solve some classic problem such as classify


#Easy to Use!!!
```c++

    NAnnBp bp;

//Init Bp Ann with 2Node InputLayer 5Node HideLayer1 3Node HideLayer2 and 1Node OutputLayer
    vector<int> layerNums = {2,5,3,1};
    bp.Init(layerNums);

//Learn And 
    vector<float> inputs = {0,0};
    vector<float> outputs = {0};
    bp.Learn(inputs,outputs);

    vector<float> inputs = {1,0};
    vector<float> outputs = {0};
    bp.Learn(inputs,outputs);

    vector<float> inputs = {0,1};
    vector<float> outputs = {0};
    bp.Learn(inputs,outputs);

    vector<float> inputs = {1,1};
    vector<float> outputs = {1};
    bp.Learn(inputs,outputs);

//Ask and Get Result
    vector<float> inputs = {0,1};
    auto res = bp.Run(inputs);

    cout<<"\tO:";
    foreach(auto r , res){
        cout<<r<<",";
    }
    cout<<endl;
```