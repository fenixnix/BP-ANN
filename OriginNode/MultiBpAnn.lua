_G['os'] = nil
_G['io'] = nil
json = require 'json'

gUser = nil 

function init()
    print('Hello BP ANN!')
    math.randomseed(0)
end

function setUser(pUser) 
    gUser = pUser 
end

function str2hex(pVar)  
    local hexstr  
    local charcode  
    local allhexstr = ''
    local bytes = pVar
    for i = 1, string.len(bytes) do  
        local charcode = tonumber(string.byte(bytes, i, i));  
        local hexstr = string.format("%02X", charcode);  
        allhexstr=allhexstr..hexstr  
    end
    return allhexstr;  
end  

function hex2str(pVar)  
    local allhexstr = ''
    for i = 1, string.len(pVar) - 1, 2 do  
        local doublebytestr = string.sub(pVar, i, i+1);  
        local n = tonumber(doublebytestr, 16);  
        allhexstr=allhexstr..string.format("%c", n)
    end
    return allhexstr
end

ann = {}
anns = {}
lambda = 0.05

function _Sigmoid(signal)
    result = 1.0/(1.0+ math.exp(-1*signal))
    return result
end

function _InitNerve(wtCnt)
    local n = {}
    n[0] = 0; --Bias
    for i = 1 , wtCnt, 1 do
        n[i] = math.random()
    end
    return n
end

function _InitLayer(wtCnt,nCnt)
    local l = {}
    l[0] = wtCnt --Weight Num
    for i = 1, nCnt do
        l[i] = _InitNerve(wtCnt)
    end
    return l
end

function _InitBpAnn(layerNum)
    local bpAnn = {}
    for i = 1,#layerNum-1  do
        bpAnn[i] = _InitLayer(layerNum[i],layerNum[i+1])
    end
    return bpAnn
end

function _PrintBpAnn(bpAnn)
    for i = 1,#bpAnn do
        print('L:'..i..'# WtCt:'..bpAnn[i][0]..';')
        for j = 1,#bpAnn[i] do 
           print('\tN:'..j..'# NCt:'..#bpAnn[i][j]..' Bias:'..bpAnn[i][j][0]..';') 
            for k = 1,#bpAnn[i][j] do
                print('\t\t'..bpAnn[i][j][k])
            end
        end
    end
end

function _RunNerve(nerv,inputs)
    local s = nerv[0]
    for i = 1,#inputs,1 do
        s = s + inputs[i]*nerv[i]
    end
    return _Sigmoid(s);
end

function _TeachNerve(nerv,inputs,err)
    local O = _RunNerve(nerv,inputs)
    local E = O*(1.0-O)*err
    for i = 1,#inputs,1 do
        nerv[i] = nerv[i] + lambda*E*inputs[i]
    end
    nerv[0] = nerv[0]+lambda*E
    return E
end

function _TeachNerveO(nerv,inputs,taget)
    local O = _RunNerve(nerv,inputs)
    return _TeachNerve(nerv,inputs,taget - O)
end

function _RunLayer(layer,inputs)
    local O = {}
    for i = 1, #layer,1 do
        O[i] = _RunNerve(layer[i],inputs)
    end
    return O
end

function _getBpErrs(layer,errs)
    local bpErrs = {}
    for i = 1,layer[0] do
        local bpErrSum = 0;
        for j = 1 ,#layer  do
            bpErrSum = bpErrSum + errs[j]*layer[j][i];
        end
        bpErrs[i] = bpErrSum;
    end
    return bpErrs;
end

function _TeachLayerO(layer, inputs, outputs)
    local errs = {}
    for i = 1,#layer do
        errs[i] = _TeachNerveO(layer[i],inputs,outputs[i])
    end
    return _getBpErrs(layer,errs);
end

function _TeachLayer(layer, inputs, errors)
    local errs = {}
    for i = 1,#layer do
        errs[i] = _TeachNerve(layer[i],inputs,errors[i])
    end
    return _getBpErrs(layer,errs);
end

function _RunBpAnn(bpAnn, inputs)
    local result = inputs;
    for i = 1, #bpAnn do
        result = _RunLayer(bpAnn[i],result)
    end
    return result;
end

function _RunBpGetAllLayerOutputs(bpAnn, inputs)
    local outputs = {} --2D array
    local result = inputs
    for i = 1, #bpAnn do
        result = _RunLayer(bpAnn[i],result)
        outputs[i] = result
    end
    return outputs;
end

function _LearnBpAnn(bpAnn, input, output)
    local outputs = _RunBpGetAllLayerOutputs(bpAnn,input)
    outputs[0] = input
    local bp = _TeachLayerO(bpAnn[#bpAnn],outputs[#outputs-1],output)
    for i = #bpAnn-1,1,-1 do
        bp = _TeachLayer(bpAnn[i],outputs[i-1],bp)
    end
end

--[[
OriginNode Contract Code
{'input':[1,2,3,4]}
--]]

--"{"ID":"XOR","PARA":[2,5,1]}"
function createAnn(inputString)
    local str = hex2str(inputString)
    local input = json.decode(str)
    anns[input['ID']] = _InitBpAnn(input['PARA'])
    _PrintBpAnn(ann)
end

--"{"ID":"XOR","I":[0,1]}"
function getAsk(inputString)
    local str = hex2str(inputString)
    local input = json.decode(str)
    local O = _RunBpAnn(anns[input['ID']],input['I'])
    return json.encode({output=O})
end

--"{"ID":"XOR","I":[0,1],"O":[1]}"
function teach(inputString)
    local str = hex2str(inputString)
    local input = json.decode(str)
    local O = _LearnBpAnn(anns[input['ID']],input['I'],input['O'])
    return str.." OK!"
end

--[[
SelfTest Code
--]]

function testTeach(times)
    print('Teach XOR')
    str = '{"ID":"XOR","I":[0,0],"O":[0]}'
    t1 = str2hex(str)
    str = '{"ID":"XOR","I":[0,1],"O":[1]}'
    t2 = str2hex(str)
    str = '{"ID":"XOR","I":[1,0],"O":[1]}'
    t3 = str2hex(str)
    str = '{"ID":"XOR","I":[1,1],"O":[0]}'
    t4 = str2hex(str)

    for i = times , 1, -1 
    do  
        teach(t1)
        teach(t2)
        teach(t3)
        teach(t4)
    end
end

function testAsk()
    print('Results:')
    str = '{"ID":"XOR","I":[0,0]}'
    res = getAsk(str2hex(str))
    print(res)
    str = '{"ID":"XOR","I":[0,1]}'
    res = getAsk(str2hex(str))
    print(res)
    str = '{"ID":"XOR","I":[1,0]}'
    res = getAsk(str2hex(str))
    print(res)
    str = '{"ID":"XOR","I":[1,1]}'
    res = getAsk(str2hex(str))
    print(res)
end

function test()
    str = '{"ID":"XOR","PARA":[2,5,1]}'
    createAnn(str2hex(str))

    testAsk()

    testTeach(5000)
    testAsk()
    
    testTeach(5000)
    testAsk()
    
    testTeach(5000)
    testAsk()
end

test()